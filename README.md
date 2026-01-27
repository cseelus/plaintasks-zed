# PlainTasks for Zed

A Zed extension for managing todo lists with syntax highlighting and interactive task management. Inspired by [Todo+](https://github.com/fabiospampinato/vscode-todo-plus) for VSCode and [PlainTasks](https://github.com/aziz/PlainTasks) for Sublime Text.

## Features

- ✅ **Syntax highlighting** for `.todo`, `.tasks`, and `.taskpaper` files
- ✅ **Interactive task management** via Language Server Protocol
- ✅ **Code actions** to toggle task states (Done/Cancelled/Pending)
- ✅ **Automatic timestamps** when marking tasks complete
- ✅ **Tag completion** - type `@` to see suggestions
- ✅ **Project outline** - navigate between projects via symbol picker
- ✅ **Priority tags** with special colors (`@critical`, `@high`, `@today`, `@low`)

## Quick Start

### 1. Install the Extension

Search for "PlainTasks" in the Zed extensions panel (`Cmd+Shift+X`).

### 2. Set Up Keybindings (Required!)

**Zed extensions cannot automatically add keybindings** - you need to configure them manually.

Open your keymap (`Cmd+K, Cmd+S` or *Zed → Settings → Open Keymap*) and add:

#### Standard Keybindings

```json
[
  {
    "context": "Editor && language == Todo",
    "bindings": {
      "alt-d": "editor::ToggleCodeActions",
      "alt-c": "editor::ToggleCodeActions"
    }
  }
]
```

- **Alt+D**: Toggle task (Done/Pending)
- **Alt+C**: Toggle task or Mark as Cancelled

#### Vim Mode Keybindings

```json
[
  {
    "context": "Editor && language == Todo && VimControl && !VimWaiting && !menu",
    "bindings": {
      "+": ["workspace::SendKeystrokes", "o ☐ escape"],
      "=": "editor::ToggleCodeActions",
      "ctrl-m": "editor::ToggleCodeActions"
    }
  }
]
```

- **`+`** (normal mode): Create new task
- **`=`** (normal mode): Toggle Done/Pending
- **`Ctrl+M`** (normal mode): Mark as Cancelled

> 💡 **Tip**: The LSP automatically applies the most relevant action based on context, so pressing `=` directly toggles tasks without showing a menu!

For more keybinding options, see [KEYBINDINGS.md](KEYBINDINGS.md).

## Usage

### Task Management

Put your cursor on a task and use code actions (or your configured keybindings):

| Current State | Action | Result |
|--------------|--------|--------|
| `☐ Task` | Mark as Done | `✔ Task @done(25-12-31 00:30)` |
| `☐ Task` | Mark as Cancelled | `✘ Task @cancelled(25-12-31 00:30)` |
| `✔ Task @done(...)` | Revert to Pending | `☐ Task` |
| `✘ Task @cancelled(...)` | Revert to Pending | `☐ Task` |

### Tag Completion

Type `@` and you'll see suggestions for:
- Common tags: `@today`, `@high`, `@medium`, `@low`, `@critical`
- Time tags: `@done`, `@cancelled`, `@started`, `@est`, `@lasted`
- Any tags you've already used in the document

### File Format

```
Project Name:
  ☐ Pending task @today
  ✔ Completed task @done(25-01-18 14:30)
  ✘ Cancelled task @cancelled(25-01-18 15:00)
  
  Notes and comments without a symbol
  
  Sub Project:
    ☐ Nested task @high @est(2h)

Archive:
  ✔ Old completed task @done(25-01-17 09:00)
```

## Screenshot

![PlainTasks screenshot](https://github.com/cseelus/plaintasks-zed/blob/main/screenshot.png)

## Supported File Extensions

- `.todo`, `.todos`
- `.task`, `.tasks`
- `.taskpaper`

## How It Works

PlainTasks uses two components:

1. **Tree-sitter Grammar**: Provides syntax highlighting and project outline
2. **Language Server (LSP)**: Provides interactive features like code actions and tag completion

The LSP server (`plaintasks-lsp`) runs automatically when you open a `.todo` file.

## Development

### Prerequisites

- Rust installed via [rustup](https://rustup.rs/) (required by Zed for extension development)
- The `wasm32-wasip1` target for building the extension

### Quick Start

```bash
# 1. Setup (one-time)
make setup

# 2. Build and install LSP server
make install-lsp

# 3. Build extension for development
make dev-extension

# 4. Install in Zed
# Open Zed → Extensions (Cmd+Shift+X) → Install Dev Extension → Select this directory
```

### Build Commands

```bash
make help              # Show all available commands
make setup             # Install Rust targets and check dependencies
make build             # Build extension (debug) + LSP server
make build-release     # Build extension (release) + LSP server
make install-lsp       # Build and install LSP to ~/.cargo/bin/
make dev-extension     # Build everything for dev extension use
make clean             # Remove all build artifacts
```

### Manual Building

If you prefer not to use the Makefile:

```bash
# Install the wasm32-wasip1 target
rustup target add wasm32-wasip1

# Build the extension
cargo build --release --target wasm32-wasip1
ln -sf target/wasm32-wasip1/release/plaintasks.wasm extension.wasm

# Build and install the LSP server
cd lsp
cargo build --release
cp target/release/plaintasks-lsp ~/.cargo/bin/
```

### Project Structure

- `src/extension.rs` - Zed extension (WASM component)
- `lsp/` - Language Server Protocol implementation (native binary)
- `grammars/todo/` - Tree-sitter grammar (separate repo: [tree-sitter-todo](https://github.com/cseelus/tree-sitter-todo))
- `languages/todo/` - Language configuration

## Troubleshooting

**Code actions not working?**
- Make sure you've added keybindings to your `keymap.json`
- Check that the file has a `.todo` extension
- Try restarting Zed (`Cmd+Q` and reopen)

**Tag completion not showing?**
- Type `@` and wait a moment
- Check if Copilot or other completion providers are overriding it
- Try pressing `Ctrl+Space` to manually trigger completion

**LSP not starting?**
- Check Zed's logs: `tail -f ~/Library/Logs/Zed/Zed.log | grep plaintasks`
- Reinstall the extension

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## Roadmap

- [x] Tree-sitter grammar with syntax highlighting
- [x] Language Server Protocol implementation
- [x] Code actions for task state management
- [x] Tag completion
- [x] Project outline support
- [ ] Archive functionality (move completed tasks)
- [ ] Create new task command
- [ ] Statistics view (task counts, time tracking)

## License

MIT

## Acknowledgments

- Inspired by [PlainTasks](https://github.com/aziz/PlainTasks) for Sublime Text
- Based on [Todo+](https://github.com/fabiospampinato/vscode-todo-plus) for VSCode
