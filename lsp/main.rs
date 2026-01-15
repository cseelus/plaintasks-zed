use lazy_static::lazy_static;
use regex::Regex;
use std::collections::HashMap;
use tower_lsp::jsonrpc::Result;
use tower_lsp::lsp_types::*;
use tower_lsp::{Client, LanguageServer, LspService, Server};

lazy_static! {
    static ref PENDING_PATTERN: Regex = Regex::new(r"^(\s*)☐\s+(.*)$").unwrap();
    static ref DONE_PATTERN: Regex = Regex::new(r"^(\s*)✔\s+(.*)$").unwrap();
    static ref CANCELLED_PATTERN: Regex = Regex::new(r"^(\s*)✘\s+(.*)$").unwrap();
    static ref DONE_TAG: Regex = Regex::new(r"\s*@done\([^)]+\)").unwrap();
    static ref CANCELLED_TAG: Regex = Regex::new(r"\s*@cancelled\([^)]+\)").unwrap();
    static ref TAG_PATTERN: Regex = Regex::new(r"@(\w+)").unwrap();
}

#[derive(Debug)]
struct DocumentState {
    content: String,
}

struct Backend {
    client: Client,
    documents: tokio::sync::RwLock<HashMap<String, DocumentState>>,
}

impl Backend {
    fn new(client: Client) -> Self {
        Self {
            client,
            documents: tokio::sync::RwLock::new(HashMap::new()),
        }
    }

    fn get_current_timestamp() -> String {
        chrono::Local::now().format("%y-%m-%d %H:%M").to_string()
    }

    fn get_line_at_position(&self, content: &str, position: Position) -> Option<(String, usize, usize)> {
        let lines: Vec<&str> = content.lines().collect();
        if position.line as usize >= lines.len() {
            return None;
        }
        let line = lines[position.line as usize].to_string();
        let line_start = lines[..position.line as usize]
            .iter()
            .map(|l| l.len() + 1)
            .sum();
        let line_end = line_start + line.len();
        Some((line, line_start, line_end))
    }
}

#[tower_lsp::async_trait]
impl LanguageServer for Backend {
    async fn initialize(&self, _: InitializeParams) -> Result<InitializeResult> {
        Ok(InitializeResult {
            capabilities: ServerCapabilities {
                text_document_sync: Some(TextDocumentSyncCapability::Kind(
                    TextDocumentSyncKind::FULL,
                )),
                completion_provider: Some(CompletionOptions {
                    trigger_characters: Some(vec!["@".to_string()]),
                    ..Default::default()
                }),
                code_action_provider: Some(CodeActionProviderCapability::Simple(true)),
                ..Default::default()
            },
            ..Default::default()
        })
    }

    async fn initialized(&self, _: InitializedParams) {
        self.client
            .log_message(MessageType::INFO, "PlainTasks LSP initialized")
            .await;
    }

    async fn did_open(&self, params: DidOpenTextDocumentParams) {
        let uri = params.text_document.uri.to_string();
        let content = params.text_document.text;

        self.documents.write().await.insert(
            uri,
            DocumentState { content },
        );
    }

    async fn did_change(&self, params: DidChangeTextDocumentParams) {
        let uri = params.text_document.uri.to_string();
        if let Some(change) = params.content_changes.first() {
            if let Some(doc) = self.documents.write().await.get_mut(&uri) {
                doc.content = change.text.clone();
            }
        }
    }

    async fn did_close(&self, params: DidCloseTextDocumentParams) {
        let uri = params.text_document.uri.to_string();
        self.documents.write().await.remove(&uri);
    }

    async fn completion(&self, params: CompletionParams) -> Result<Option<CompletionResponse>> {
        let uri = params.text_document_position.text_document.uri.to_string();
        let documents = self.documents.read().await;

        if let Some(doc) = documents.get(&uri) {
            // Extract all existing tags from the document
            let mut tags = std::collections::HashSet::new();
            for cap in TAG_PATTERN.captures_iter(&doc.content) {
                if let Some(tag) = cap.get(1) {
                    tags.insert(tag.as_str().to_string());
                }
            }

            // Common tags to suggest
            let common_tags = vec!["today", "high", "medium", "low", "critical",
                                   "done", "cancelled", "started", "est", "lasted"];

            for tag in common_tags {
                tags.insert(tag.to_string());
            }

            let items: Vec<CompletionItem> = tags
                .into_iter()
                .map(|tag| CompletionItem {
                    label: format!("@{}", tag),
                    kind: Some(CompletionItemKind::KEYWORD),
                    insert_text: Some(tag),
                    ..Default::default()
                })
                .collect();

            return Ok(Some(CompletionResponse::Array(items)));
        }

        Ok(None)
    }

    async fn code_action(&self, params: CodeActionParams) -> Result<Option<CodeActionResponse>> {
        let uri = params.text_document.uri.to_string();
        let position = params.range.start;
        let documents = self.documents.read().await;

        if let Some(doc) = documents.get(&uri) {
            if let Some((line, _line_start, _line_end)) = self.get_line_at_position(&doc.content, position) {
                let mut actions = Vec::new();

                // Check for pending task
                if PENDING_PATTERN.is_match(&line) {
                    // Mark as Done
                    if let Some(caps) = PENDING_PATTERN.captures(&line) {
                        let indent = caps.get(1).map_or("", |m| m.as_str());
                        let content = caps.get(2).map_or("", |m| m.as_str());
                        let new_line = format!("{}✔ {} @done({})", indent, content, Self::get_current_timestamp());

                        actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                            title: "Mark as Done".to_string(),
                            kind: Some(CodeActionKind::QUICKFIX),
                            is_preferred: Some(true),
                            edit: Some(WorkspaceEdit {
                                changes: Some(HashMap::from([(
                                    params.text_document.uri.clone(),
                                    vec![TextEdit {
                                        range: Range {
                                            start: Position { line: position.line, character: 0 },
                                            end: Position { line: position.line, character: u32::MAX },
                                        },
                                        new_text: new_line,
                                    }],
                                )])),
                                ..Default::default()
                            }),
                            ..Default::default()
                        }));
                    }

                    // Mark as Cancelled
                    if let Some(caps) = PENDING_PATTERN.captures(&line) {
                        let indent = caps.get(1).map_or("", |m| m.as_str());
                        let content = caps.get(2).map_or("", |m| m.as_str());
                        let new_line = format!("{}✘ {} @cancelled({})", indent, content, Self::get_current_timestamp());

                        actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                            title: "Mark as Cancelled".to_string(),
                            kind: Some(CodeActionKind::QUICKFIX),
                            edit: Some(WorkspaceEdit {
                                changes: Some(HashMap::from([(
                                    params.text_document.uri.clone(),
                                    vec![TextEdit {
                                        range: Range {
                                            start: Position { line: position.line, character: 0 },
                                            end: Position { line: position.line, character: u32::MAX },
                                        },
                                        new_text: new_line,
                                    }],
                                )])),
                                ..Default::default()
                            }),
                            ..Default::default()
                        }));
                    }
                }

                // Check for done task
                if DONE_PATTERN.is_match(&line) {
                    if let Some(caps) = DONE_PATTERN.captures(&line) {
                        let indent = caps.get(1).map_or("", |m| m.as_str());
                        let content = caps.get(2).map_or("", |m| m.as_str());
                        let content_clean = DONE_TAG.replace_all(content, "").trim().to_string();
                        let new_line = format!("{}☐ {}", indent, content_clean);

                        actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                            title: "Revert to Pending".to_string(),
                            kind: Some(CodeActionKind::QUICKFIX),
                            is_preferred: Some(true),
                            edit: Some(WorkspaceEdit {
                                changes: Some(HashMap::from([(
                                    params.text_document.uri.clone(),
                                    vec![TextEdit {
                                        range: Range {
                                            start: Position { line: position.line, character: 0 },
                                            end: Position { line: position.line, character: u32::MAX },
                                        },
                                        new_text: new_line,
                                    }],
                                )])),
                                ..Default::default()
                            }),
                            ..Default::default()
                        }));
                    }
                }

                // Check for cancelled task
                if CANCELLED_PATTERN.is_match(&line) {
                    if let Some(caps) = CANCELLED_PATTERN.captures(&line) {
                        let indent = caps.get(1).map_or("", |m| m.as_str());
                        let content = caps.get(2).map_or("", |m| m.as_str());
                        let content_clean = CANCELLED_TAG.replace_all(content, "").trim().to_string();
                        let new_line = format!("{}☐ {}", indent, content_clean);

                        actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                            title: "Revert to Pending".to_string(),
                            kind: Some(CodeActionKind::QUICKFIX),
                            is_preferred: Some(true),
                            edit: Some(WorkspaceEdit {
                                changes: Some(HashMap::from([(
                                    params.text_document.uri.clone(),
                                    vec![TextEdit {
                                        range: Range {
                                            start: Position { line: position.line, character: 0 },
                                            end: Position { line: position.line, character: u32::MAX },
                                        },
                                        new_text: new_line,
                                    }],
                                )])),
                                ..Default::default()
                            }),
                            ..Default::default()
                        }));
                    }
                }

                // Check if line is NOT a todo and NOT a project - offer to convert
                let is_todo = PENDING_PATTERN.is_match(&line) ||
                              DONE_PATTERN.is_match(&line) ||
                              CANCELLED_PATTERN.is_match(&line);
                let is_project = line.trim_end().ends_with(':');

                if !is_todo && !is_project {
                    // Extract current indentation
                    let indent = line.chars()
                        .take_while(|c| c.is_whitespace())
                        .collect::<String>();

                    // Get content after indentation
                    let content = line.trim_start();

                    // Create new line with todo symbol
                    let new_line = if content.is_empty() {
                        format!("{}☐ ", indent)
                    } else {
                        format!("{}☐ {}", indent, content)
                    };

                    actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                        title: "Convert to Todo item".to_string(),
                        kind: Some(CodeActionKind::REFACTOR),
                        is_preferred: Some(true),
                        edit: Some(WorkspaceEdit {
                            changes: Some(HashMap::from([(
                                params.text_document.uri.clone(),
                                vec![TextEdit {
                                    range: Range {
                                        start: Position { line: position.line, character: 0 },
                                        end: Position { line: position.line, character: u32::MAX },
                                    },
                                    new_text: new_line,
                                }],
                            )])),
                            ..Default::default()
                        }),
                        ..Default::default()
                    }));
                }

                // Always offer "Insert New Todo Below" action
                // Extract indentation from current line to maintain nesting
                let indent = line.chars()
                    .take_while(|c| c.is_whitespace())
                    .collect::<String>();

                actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                    title: "Insert new Todo item below".to_string(),
                    kind: Some(CodeActionKind::REFACTOR),
                    edit: Some(WorkspaceEdit {
                        changes: Some(HashMap::from([(
                            params.text_document.uri.clone(),
                            vec![TextEdit {
                                range: Range {
                                    start: Position { line: position.line + 1, character: 0 },
                                    end: Position { line: position.line + 1, character: 0 },
                                },
                                new_text: format!("{}☐ \n", indent),
                            }],
                        )])),
                        ..Default::default()
                    }),
                    ..Default::default()
                }));

                if !actions.is_empty() {
                    return Ok(Some(actions));
                }
            }
        }

        Ok(None)
    }

    async fn shutdown(&self) -> Result<()> {
        Ok(())
    }
}

#[tokio::main]
async fn main() {
    let stdin = tokio::io::stdin();
    let stdout = tokio::io::stdout();

    let (service, socket) = LspService::new(|client| Backend::new(client));
    Server::new(stdin, stdout, socket).serve(service).await;
}
