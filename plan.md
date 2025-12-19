# Todo+ Migration to Zed Editor: Simplified Plan

## Overview

This document outlines a focused plan to migrate the core functionality of **Todo+** from VSCode to **Zed**. The goal is to create a lightweight, useful extension that provides:

1. **Syntax highlighting** for `.todo` files
2. **Toggle actions** to mark tasks as done/cancelled (with automatic timestamps)
3. **Archive functionality** to move completed tasks

This simplified scope delivers the essential Todo+ experience while keeping implementation straightforward.

---

## Table of Contents

1. [Target Features](#1-target-features)
2. [Architecture](#2-architecture)
3. [Implementation Guide](#3-implementation-guide)
4. [Phase 1: Tree-sitter Grammar](#4-phase-1-tree-sitter-grammar)
5. [Phase 2: Language Server](#5-phase-2-language-server)
6. [Development Checklist](#6-development-checklist)
7. [Resources](#7-resources)

---

## 1. Target Features

### Core Features (In Scope)

| Feature | Description | Implementation |
|---------|-------------|----------------|
| Syntax highlighting | Colors for projects, todos, tags, done/cancelled states | Tree-sitter grammar |
| Toggle Done | Change `☐` → `✔` and append `@done(timestamp)` | LSP code action |
| Toggle Cancelled | Change `☐` → `✘` and append `@cancelled(timestamp)` | LSP code action |
| Toggle Box | Revert `✔`/`✘` back to `☐` (remove timestamp tags) | LSP code action |
| Archive | Move all done/cancelled todos to "Archive:" section | LSP code action |
| Tag completion | Autocomplete for `@tag` names | LSP completion |
| Project outline | Navigate between projects via symbol picker | Tree-sitter outline |

### Vim Mode Keybindings

| Key | Action | Description |
|-----|--------|-------------|
| `+` | Add new task | Insert `☐ ` on new line below cursor |
| `=` | Toggle done | Toggle between `☐` ↔ `✔ @done(...)` |
| `_` | Toggle cancelled | Toggle between `☐` ↔ `✘ @cancelled(...)` |
| `-` | Archive | Move all completed/cancelled todos to Archive |

### Symbols

| State | Symbol |
|-------|--------|
| Pending | `☐` |
| Done | `✔` |
| Cancelled | `✘` |

### Out of Scope

The following VSCode Todo+ features are intentionally excluded to keep the extension simple:

- Status bar timer/statistics (no Zed API)
- Activity bar panels (no Zed API)
- Embedded todos search (use `rg` in terminal)
- 100+ configuration options
- Custom symbol configuration (fixed to `☐`, `✔`, `✘`)
- Project-level statistics

---

## 2. Architecture

### Extension Structure

```
zed-todo-plus/
├── extension.toml              # Extension manifest
├── LICENSE                     # MIT license
├── README.md                   # User documentation
├── Cargo.toml                  # Rust dependencies
├── src/
│   └── lib.rs                  # Extension entry point (LSP launcher)
├── languages/
│   └── todo/
│       ├── config.toml         # Language configuration
│       ├── highlights.scm      # Syntax highlighting
│       ├── indents.scm         # Auto-indentation
│       └── outline.scm         # Project symbols
└── grammars/
    └── tree-sitter-todo/       # Separate repository
        ├── grammar.js
        ├── package.json
        └── src/
            └── parser.c
```

### Language Server Structure

```
todo-plus-lsp/
├── Cargo.toml
└── src/
    ├── main.rs                 # LSP server entry
    ├── parser.rs               # Todo document parsing
    └── actions.rs              # Toggle/archive logic
```

### How It Works

```
┌─────────────────────────────────────────────────────────────┐
│                         Zed Editor                          │
├─────────────────────────────────────────────────────────────┤
│  .todo file                                                 │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Project:                     ← highlighted as heading │  │
│  │   ☐ Task one @today          ← box + tag highlighting │  │
│  │   ✔ Task two @done(25-01-18) ← done styling           │  │
│  └───────────────────────────────────────────────────────┘  │
│                          │                                  │
│              Tree-sitter │ parsing                          │
│                          ▼                                  │
│  ┌───────────────────────────────────────────────────────┐  │
│  │              Syntax Highlighting                       │  │
│  │              Symbol Outline (projects)                 │  │
│  └───────────────────────────────────────────────────────┘  │
│                                                             │
│  User triggers code action (Cmd+.)                          │
│                          │                                  │
│                          ▼                                  │
│  ┌───────────────────────────────────────────────────────┐  │
│  │              todo-plus-lsp                             │  │
│  │  • "Mark as Done" → ☐ → ✔ + @done(timestamp)          │  │
│  │  • "Mark as Cancelled" → ☐ → ✘ + @cancelled(...)      │  │
│  │  • "Archive Completed" → move to Archive section       │  │
│  │  • Tag completions when typing @                       │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
```

---

## 3. Implementation Guide

### Prerequisites

- Rust installed via `rustup`
- Node.js (for Tree-sitter grammar development)
- Zed editor (latest version)

### Development Workflow

1. **Create Tree-sitter grammar** in a separate repository
2. **Create Zed extension** that references the grammar
3. **Build Language Server** as a standalone Rust binary
4. **Integrate LSP** into the Zed extension
5. **Test and publish**

---

## 4. Phase 1: Tree-sitter Grammar

### 4.1 Grammar Repository Setup

Create a new repository: `tree-sitter-todo`

```bash
mkdir tree-sitter-todo && cd tree-sitter-todo
npm init -y
npm install tree-sitter-cli
```

### 4.2 Grammar Definition (grammar.js)

```javascript
/// <reference types="tree-sitter-cli/dsl" />

module.exports = grammar({
  name: 'todo',

  extras: $ => [/\r/],

  rules: {
    // Document is a list of lines
    document: $ => repeat(choice(
      $.project,
      $.todo_done,
      $.todo_cancelled,
      $.todo_box,
      $.comment,
      $.empty_line
    )),

    // Project: text ending with colon
    project: $ => seq(
      /[^\n\r:]+/,
      ':',
      optional($.tag_list),
      $._newline
    ),

    // Pending todo (has box symbol)
    todo_box: $ => seq(
      $._indent,
      $.box_symbol,
      ' ',
      $.content,
      $._newline
    ),

    // Completed todo (has done symbol)
    todo_done: $ => seq(
      $._indent,
      $.done_symbol,
      ' ',
      $.content,
      $._newline
    ),

    // Cancelled todo (has cancelled symbol)
    todo_cancelled: $ => seq(
      $._indent,
      $.cancelled_symbol,
      ' ',
      $.content,
      $._newline
    ),

    // Box symbol for pending todos
    box_symbol: $ => '☐',

    // Done symbol
    done_symbol: $ => '✔',

    // Cancelled symbol
    cancelled_symbol: $ => '✘',

    // Task content (text with optional tags and formatting)
    content: $ => repeat1(choice(
      $.tag,
      $.formatted_bold,
      $.formatted_italic,
      $.formatted_code,
      $.text
    )),

    // Tags: @name or @name(value)
    tag: $ => seq(
      '@',
      $.tag_name,
      optional(seq('(', $.tag_value, ')'))
    ),

    tag_name: $ => /[a-zA-Z][a-zA-Z0-9_-]*/,
    tag_value: $ => /[^)\n\r]+/,
    tag_list: $ => repeat1($.tag),

    // Markdown-style formatting
    formatted_bold: $ => seq('*', /[^*\n\r]+/, '*'),
    formatted_italic: $ => seq('_', /[^_\n\r]+/, '_'),
    formatted_code: $ => seq('`', /[^`\n\r]+/, '`'),

    // Plain text (anything not a tag or formatting)
    text: $ => /[^\n\r@*_`]+/,

    // Comment (line without todo symbol or project colon)
    comment: $ => seq(
      $._indent,
      /[^☐✔✘\n\r][^\n\r]*/,
      $._newline
    ),

    // Whitespace handling
    _indent: $ => /[ \t]*/,
    _newline: $ => /\n/,
    empty_line: $ => /\n/
  }
});
```

### 4.3 Syntax Highlighting (queries/highlights.scm)

```scheme
; Projects - heading style
(project) @markup.heading

; Todo states
(box_symbol) @punctuation.special
(done_symbol) @string.special
(cancelled_symbol) @constant

; Done todos - muted appearance
(todo_done (content)) @comment
(todo_done (done_symbol)) @string.special

; Cancelled todos - strikethrough style
(todo_cancelled (content)) @comment.unused
(todo_cancelled (cancelled_symbol)) @constant

; Tags
(tag "@" @punctuation.special)
(tag_name) @attribute
(tag_value) @string

; Special priority tags
((tag_name) @keyword.exception
 (#any-of? @keyword.exception "critical" "high" "important"))

((tag_name) @hint
 (#any-of? @hint "low" "maybe" "someday"))

((tag_name) @keyword.modifier
 (#eq? @keyword.modifier "today"))

; Time-related tags
((tag_name) @type.builtin
 (#any-of? @type.builtin "created" "started" "done" "cancelled" "lasted" "est"))

; Formatting
(formatted_bold) @markup.bold
(formatted_italic) @markup.italic
(formatted_code) @markup.raw

; Comments
(comment) @comment

; Archive section
((project) @comment.documentation
 (#match? @comment.documentation "^Archive:"))
```

### 4.4 Language Configuration (languages/todo/config.toml)

```toml
name = "Todo"
grammar = "todo"
path_suffixes = ["todo", "todos", "task", "tasks", "taskpaper"]
line_comments = ["# "]
tab_size = 2
hard_tabs = false
```

### 4.5 Indentation Rules (languages/todo/indents.scm)

```scheme
; Indent after projects
(project) @indent

; Maintain indentation for todos
(todo_box) @indent.always
(todo_done) @indent.always
(todo_cancelled) @indent.always
```

### 4.6 Outline Support (languages/todo/outline.scm)

```scheme
; Show projects in symbol outline
(project) @item
```

### 4.7 Extension Manifest (extension.toml)

```toml
id = "todo-plus"
name = "Todo+"
version = "0.1.0"
schema_version = 1
authors = ["Your Name <you@example.com>"]
description = "Manage todo lists with ease. Toggle tasks, add timestamps, and archive completed items."
repository = "https://github.com/your-name/zed-todo-plus"

[grammars.todo]
repository = "https://github.com/your-name/tree-sitter-todo"
rev = "main"

[language_servers.todo-plus-lsp]
name = "Todo+"
languages = ["todo"]
```

---

## 5. Phase 2: Language Server

### 5.1 Project Setup

```bash
cargo new todo-plus-lsp
cd todo-plus-lsp
```

### 5.2 Dependencies (Cargo.toml)

```toml
[package]
name = "todo-plus-lsp"
version = "0.1.0"
edition = "2021"

[[bin]]
name = "todo-plus-lsp"
path = "src/main.rs"

[dependencies]
tower-lsp = "0.20"
tokio = { version = "1", features = ["full"] }
serde = { version = "1", features = ["derive"] }
serde_json = "1"
chrono = "0.4"
regex = "1"
ropey = "1"  # Efficient text rope for document handling
```

### 5.3 Main Server (src/main.rs)

```rust
use chrono::Local;
use regex::Regex;
use ropey::Rope;
use std::collections::HashMap;
use std::sync::RwLock;
use tower_lsp::jsonrpc::Result;
use tower_lsp::lsp_types::*;
use tower_lsp::{Client, LanguageServer, LspService, Server};

// Document storage
struct DocumentState {
    content: Rope,
}

struct Backend {
    client: Client,
    documents: RwLock<HashMap<Url, DocumentState>>,
}

// Regex patterns for todo parsing
lazy_static::lazy_static! {
    static ref BOX_PATTERN: Regex = Regex::new(r"^(\s*)(☐)(\s+)(.*)$").unwrap();
    static ref DONE_PATTERN: Regex = Regex::new(r"^(\s*)(✔)(\s+)(.*)$").unwrap();
    static ref CANCELLED_PATTERN: Regex = Regex::new(r"^(\s*)(✘)(\s+)(.*)$").unwrap();
    static ref DONE_TAG: Regex = Regex::new(r"\s*@done\([^)]*\)").unwrap();
    static ref CANCELLED_TAG: Regex = Regex::new(r"\s*@cancelled\([^)]*\)").unwrap();
}

impl Backend {
    fn new(client: Client) -> Self {
        Backend {
            client,
            documents: RwLock::new(HashMap::new()),
        }
    }

    fn get_current_timestamp(&self) -> String {
        Local::now().format("%y-%m-%d %H:%M").to_string()
    }

    fn get_line_at_position(&self, uri: &Url, line: u32) -> Option<String> {
        let docs = self.documents.read().ok()?;
        let doc = docs.get(uri)?;
        let line_idx = line as usize;
        if line_idx < doc.content.len_lines() {
            Some(doc.content.line(line_idx).to_string())
        } else {
            None
        }
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
            .log_message(MessageType::INFO, "Todo+ LSP initialized")
            .await;
    }

    async fn did_open(&self, params: DidOpenTextDocumentParams) {
        let mut docs = self.documents.write().unwrap();
        docs.insert(
            params.text_document.uri,
            DocumentState {
                content: Rope::from_str(&params.text_document.text),
            },
        );
    }

    async fn did_change(&self, params: DidChangeTextDocumentParams) {
        let mut docs = self.documents.write().unwrap();
        if let Some(change) = params.content_changes.into_iter().next() {
            docs.insert(
                params.text_document.uri,
                DocumentState {
                    content: Rope::from_str(&change.text),
                },
            );
        }
    }

    async fn did_close(&self, params: DidCloseTextDocumentParams) {
        let mut docs = self.documents.write().unwrap();
        docs.remove(&params.text_document.uri);
    }

    async fn completion(&self, _params: CompletionParams) -> Result<Option<CompletionResponse>> {
        let items = vec![
            CompletionItem {
                label: "today".to_string(),
                kind: Some(CompletionItemKind::KEYWORD),
                detail: Some("Mark as due today".to_string()),
                insert_text: Some("today".to_string()),
                ..Default::default()
            },
            CompletionItem {
                label: "critical".to_string(),
                kind: Some(CompletionItemKind::KEYWORD),
                detail: Some("Critical priority".to_string()),
                insert_text: Some("critical".to_string()),
                ..Default::default()
            },
            CompletionItem {
                label: "high".to_string(),
                kind: Some(CompletionItemKind::KEYWORD),
                detail: Some("High priority".to_string()),
                insert_text: Some("high".to_string()),
                ..Default::default()
            },
            CompletionItem {
                label: "low".to_string(),
                kind: Some(CompletionItemKind::KEYWORD),
                detail: Some("Low priority".to_string()),
                insert_text: Some("low".to_string()),
                ..Default::default()
            },
            CompletionItem {
                label: "started".to_string(),
                kind: Some(CompletionItemKind::KEYWORD),
                detail: Some("Start time tracking".to_string()),
                insert_text: Some(format!("started({})", Local::now().format("%y-%m-%d %H:%M"))),
                ..Default::default()
            },
            CompletionItem {
                label: "est".to_string(),
                kind: Some(CompletionItemKind::KEYWORD),
                detail: Some("Time estimate".to_string()),
                insert_text: Some("est($0)".to_string()),
                insert_text_format: Some(InsertTextFormat::SNIPPET),
                ..Default::default()
            },
        ];
        Ok(Some(CompletionResponse::Array(items)))
    }

    async fn code_action(&self, params: CodeActionParams) -> Result<Option<CodeActionResponse>> {
        let uri = &params.text_document.uri;
        let line = params.range.start.line;
        
        let Some(line_text) = self.get_line_at_position(uri, line) else {
            return Ok(None);
        };

        let mut actions = Vec::new();
        let timestamp = self.get_current_timestamp();

        // Check if line is a pending todo (has box symbol)
        if let Some(caps) = BOX_PATTERN.captures(&line_text) {
            let indent = caps.get(1).map_or("", |m| m.as_str());
            let space = caps.get(3).map_or(" ", |m| m.as_str());
            let content = caps.get(4).map_or("", |m| m.as_str());

            // Action: Mark as Done
            let new_text = format!("{}✔{}{} @done({})\n", indent, space, content, timestamp);
            actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                title: "Mark as Done".to_string(),
                kind: Some(CodeActionKind::QUICKFIX),
                edit: Some(WorkspaceEdit {
                    changes: Some(HashMap::from([(
                        uri.clone(),
                        vec![TextEdit {
                            range: Range {
                                start: Position { line, character: 0 },
                                end: Position { line: line + 1, character: 0 },
                            },
                            new_text,
                        }],
                    )])),
                    ..Default::default()
                }),
                ..Default::default()
            }));

            // Action: Mark as Cancelled
            let new_text = format!("{}✘{}{} @cancelled({})\n", indent, space, content, timestamp);
            actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                title: "Mark as Cancelled".to_string(),
                kind: Some(CodeActionKind::QUICKFIX),
                edit: Some(WorkspaceEdit {
                    changes: Some(HashMap::from([(
                        uri.clone(),
                        vec![TextEdit {
                            range: Range {
                                start: Position { line, character: 0 },
                                end: Position { line: line + 1, character: 0 },
                            },
                            new_text,
                        }],
                    )])),
                    ..Default::default()
                }),
                ..Default::default()
            }));
        }

        // Check if line is done - offer to revert
        if let Some(caps) = DONE_PATTERN.captures(&line_text) {
            let indent = caps.get(1).map_or("", |m| m.as_str());
            let space = caps.get(3).map_or(" ", |m| m.as_str());
            let content = caps.get(4).map_or("", |m| m.as_str());
            
            // Remove @done tag from content
            let clean_content = DONE_TAG.replace_all(content, "").trim().to_string();

            let new_text = format!("{}☐{}{}\n", indent, space, clean_content);
            actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                title: "Revert to Pending".to_string(),
                kind: Some(CodeActionKind::QUICKFIX),
                edit: Some(WorkspaceEdit {
                    changes: Some(HashMap::from([(
                        uri.clone(),
                        vec![TextEdit {
                            range: Range {
                                start: Position { line, character: 0 },
                                end: Position { line: line + 1, character: 0 },
                            },
                            new_text,
                        }],
                    )])),
                    ..Default::default()
                }),
                ..Default::default()
            }));
        }

        // Check if line is cancelled - offer to revert
        if let Some(caps) = CANCELLED_PATTERN.captures(&line_text) {
            let indent = caps.get(1).map_or("", |m| m.as_str());
            let space = caps.get(3).map_or(" ", |m| m.as_str());
            let content = caps.get(4).map_or("", |m| m.as_str());
            
            // Remove @cancelled tag from content
            let clean_content = CANCELLED_TAG.replace_all(content, "").trim().to_string();

            let new_text = format!("{}☐{}{}\n", indent, space, clean_content);
            actions.push(CodeActionOrCommand::CodeAction(CodeAction {
                title: "Revert to Pending".to_string(),
                kind: Some(CodeActionKind::QUICKFIX),
                edit: Some(WorkspaceEdit {
                    changes: Some(HashMap::from([(
                        uri.clone(),
                        vec![TextEdit {
                            range: Range {
                                start: Position { line, character: 0 },
                                end: Position { line: line + 1, character: 0 },
                            },
                            new_text,
                        }],
                    )])),
                    ..Default::default()
                }),
                ..Default::default()
            }));
        }

        // Always offer Archive action (document-wide)
        actions.push(CodeActionOrCommand::CodeAction(CodeAction {
            title: "Archive Completed".to_string(),
            kind: Some(CodeActionKind::SOURCE_ORGANIZE_IMPORTS), // Using source action kind
            edit: self.build_archive_edit(uri).await,
            ..Default::default()
        }));

        if actions.is_empty() {
            Ok(None)
        } else {
            Ok(Some(actions))
        }
    }

    async fn shutdown(&self) -> Result<()> {
        Ok(())
    }
}

impl Backend {
    /// Build a WorkspaceEdit that moves all done/cancelled todos to the Archive section
    async fn build_archive_edit(&self, uri: &Url) -> Option<WorkspaceEdit> {
        let docs = self.documents.read().ok()?;
        let doc = docs.get(uri)?;
        let content = doc.content.to_string();
        
        let mut pending_lines = Vec::new();
        let mut completed_lines = Vec::new();
        let mut archive_lines = Vec::new();
        let mut in_archive = false;
        let mut archive_start_line = None;
        
        for (i, line) in content.lines().enumerate() {
            // Check if we've hit the Archive section
            if line.trim() == "Archive:" || line.starts_with("Archive:") {
                in_archive = true;
                archive_start_line = Some(i);
                continue;
            }
            
            if in_archive {
                // Collect existing archive content
                if !line.trim().is_empty() {
                    archive_lines.push(line.to_string());
                }
            } else if DONE_PATTERN.is_match(line) || CANCELLED_PATTERN.is_match(line) {
                // This is a completed todo - move to archive
                completed_lines.push(line.to_string());
            } else {
                // Keep pending todos and other content
                pending_lines.push(line.to_string());
            }
        }
        
        // If no completed items, no edit needed
        if completed_lines.is_empty() {
            return None;
        }
        
        // Build new document content
        let mut new_content = pending_lines.join("\n");
        
        // Add Archive section
        if !new_content.ends_with("\n\n") {
            new_content.push_str("\n\n");
        }
        new_content.push_str("Archive:\n");
        
        // Add newly archived items first (most recent)
        for line in &completed_lines {
            new_content.push_str(line);
            new_content.push('\n');
        }
        
        // Add previously archived items
        for line in &archive_lines {
            new_content.push_str(line);
            new_content.push('\n');
        }
        
        let line_count = content.lines().count() as u32;
        
        Some(WorkspaceEdit {
            changes: Some(HashMap::from([(
                uri.clone(),
                vec![TextEdit {
                    range: Range {
                        start: Position { line: 0, character: 0 },
                        end: Position { line: line_count, character: 0 },
                    },
                    new_text: new_content,
                }],
            )])),
            ..Default::default()
        })
    }
}

#[tokio::main]
async fn main() {
    let stdin = tokio::io::stdin();
    let stdout = tokio::io::stdout();

    let (service, socket) = LspService::new(Backend::new);
    Server::new(stdin, stdout, socket).serve(service).await;
}
```

### 5.4 Add lazy_static dependency

Update `Cargo.toml`:

```toml
[dependencies]
# ... existing deps ...
lazy_static = "1"
```

### 5.5 Extension Entry Point (src/lib.rs)

```rust
use zed_extension_api as zed;

struct TodoPlusExtension;

impl zed::Extension for TodoPlusExtension {
    fn new() -> Self {
        TodoPlusExtension
    }

    fn language_server_command(
        &mut self,
        _language_server_id: &zed::LanguageServerId,
        _worktree: &zed::Worktree,
    ) -> zed::Result<zed::Command> {
        Ok(zed::Command {
            command: "todo-plus-lsp".to_string(),
            args: vec![],
            env: Default::default(),
        })
    }
}

zed::register_extension!(TodoPlusExtension);
```

---

## 6. Development Checklist

### Phase 1: Tree-sitter Grammar

- [ ] Create `tree-sitter-todo` repository
- [ ] Write `grammar.js` with todo/project/tag rules
- [ ] Generate parser with `tree-sitter generate`
- [ ] Write `highlights.scm` queries
- [ ] Test grammar with sample todo files
- [ ] Publish repository to GitHub

### Phase 2: Zed Extension (Grammar Only)

- [ ] Create `zed-todo-plus` repository
- [ ] Write `extension.toml` referencing grammar
- [ ] Add `languages/todo/config.toml`
- [ ] Add `languages/todo/highlights.scm`
- [ ] Add `languages/todo/indents.scm`
- [ ] Add `languages/todo/outline.scm`
- [ ] Test as dev extension in Zed
- [ ] Verify syntax highlighting works

### Phase 3: Language Server

- [ ] Create `todo-plus-lsp` Rust project
- [ ] Implement document sync
- [ ] Implement tag completion provider
- [ ] Implement "Mark as Done" code action
- [ ] Implement "Mark as Cancelled" code action
- [ ] Implement "Revert to Pending" code action
- [ ] Implement "Archive Completed" code action (optional)
- [ ] Build and test LSP binary
- [ ] Integrate LSP into Zed extension

### Phase 4: Publishing

- [ ] Write README with usage instructions
- [ ] Add LICENSE file (MIT)
- [ ] Add example `.todo` file
- [ ] Submit to Zed extensions repository

---

## 7. Resources

### Zed Documentation

- [Developing Extensions](https://zed.dev/docs/extensions/developing-extensions)
- [Language Extensions](https://zed.dev/docs/extensions/languages)
- [zed_extension_api](https://docs.rs/zed_extension_api)

### Tree-sitter

- [Creating Parsers](https://tree-sitter.github.io/tree-sitter/creating-parsers/)
- [Grammar DSL](https://tree-sitter.github.io/tree-sitter/creating-parsers/2-the-grammar-dsl.html)

### Language Server Protocol

- [LSP Specification](https://microsoft.github.io/language-server-protocol/)
- [tower-lsp crate](https://docs.rs/tower-lsp)

### Original Projects

- [vscode-todo-plus](https://github.com/fabiospampinato/vscode-todo-plus)
- [PlainTasks](https://github.com/aziz/PlainTasks)

---

## Appendix A: Keybinding Configuration

### Standard Keybindings

Users can add these keybindings to their Zed `keymap.json` for quick access:

```json
[
  {
    "context": "Editor && language == todo",
    "bindings": {
      "alt-d": "editor::ToggleCodeActions",
      "cmd-shift-a": "editor::ToggleCodeActions"
    }
  }
]
```

### Vim Mode Keybindings

For Vim users, add these bindings to trigger Todo+ actions directly from normal mode:

```json
[
  {
    "context": "Editor && language == todo && VimControl && !VimWaiting && !menu",
    "bindings": {
      "+": ["workspace::SendKeystrokes", "o ☐ space"],
      "=": "editor::ToggleCodeActions",
      "_": "editor::ToggleCodeActions",
      "-": "editor::ToggleCodeActions"
    }
  }
]
```

**Note on Vim keybindings:**

- **`+` (Add task)**: Uses `SendKeystrokes` to open a new line and insert `☐ `. This works immediately without LSP.

- **`=` / `_` / `-` (Toggle/Archive)**: These open the code action menu. The LSP will show context-appropriate actions:
  - On a pending todo (`☐`): Shows "Mark as Done" and "Mark as Cancelled"
  - On a done todo (`✔`): Shows "Revert to Pending"
  - On a cancelled todo (`✘`): Shows "Revert to Pending"
  - For archive, a document-wide action will be available

For a more streamlined experience, the LSP could be extended to support named code actions that keybindings can trigger directly:

```json
{
  "=": ["editor::ApplyCodeAction", { "name": "Toggle Done" }],
  "_": ["editor::ApplyCodeAction", { "name": "Toggle Cancelled" }],
  "-": ["editor::ApplyCodeAction", { "name": "Archive Completed" }]
}
```

*(Note: Direct code action invocation depends on Zed's keybinding capabilities. The `editor::ToggleCodeActions` approach works universally.)*

### Alternative: Single-Key Quick Actions

If you prefer single-key actions without a menu, you can use Zed's task system or external scripts. However, the code action menu approach is recommended as it:

1. Shows all available actions for the current context
2. Works consistently across different todo states
3. Requires no external dependencies

---

## Appendix B: LSP Code Action Enhancements for Vim

To make the `=`, `_`, and `-` keys more useful, the LSP should provide **preferred** code actions that Zed can auto-apply. Update the LSP to mark the primary action as preferred:

```rust
// In code_action handler, for pending todos:
actions.push(CodeActionOrCommand::CodeAction(CodeAction {
    title: "Mark as Done".to_string(),
    kind: Some(CodeActionKind::QUICKFIX),
    is_preferred: Some(true),  // This action will be auto-applied with "="
    // ... rest of action
}));
```

With `is_preferred: true`, users can potentially use keybindings like:

```json
{
  "=": "editor::ApplyPreferredCodeAction"
}
```

This would automatically apply "Mark as Done" on pending todos or "Revert to Pending" on completed todos, making `=` a true toggle key.

---

*Document updated: 2025-01-18*
*Simplified scope with Vim mode support*
