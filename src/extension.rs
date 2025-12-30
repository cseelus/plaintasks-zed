use zed_extension_api::{self as zed, Result};

struct PlainTasksExtension;

impl zed::Extension for PlainTasksExtension {
    fn new() -> Self {
        Self
    }

    fn language_server_command(
        &mut self,
        _language_server_id: &zed::LanguageServerId,
        worktree: &zed::Worktree,
    ) -> Result<zed::Command> {
        let path = worktree.which("plaintasks-lsp").ok_or_else(|| {
            "plaintasks-lsp not found in PATH".to_string()
        })?;

        Ok(zed::Command {
            command: path,
            args: vec![],
            env: Default::default(),
        })
    }
}

zed::register_extension!(PlainTasksExtension);
