# Todo+ for Zed

A Zed extension for managing todo lists with ease. Based on [Todo+](https://github.com/fabiospampinato/vscode-todo-plus) for VSCode and [PlainTasks](https://github.com/aziz/PlainTasks) for Sublime Text.

## Features

- Syntax highlighting for `.todo`, `.tasks`, and `.taskpaper` files
- Project headers with `:` suffix
- Task states: pending (`☐`), done (`✔`), cancelled (`✘`)
- Tag support (`@tag` and `@tag(value)`)
- Markdown-style formatting (*bold*, _italic_, `code`)
- Project outline navigation

## File Format

```
Project Name:
  ☐ Pending task @today
  ✔ Completed task @done(25-01-18 14:30)
  ✘ Cancelled task @cancelled(25-01-18 15:00)
  
  Notes and comments without a symbol
  
  Sub Project:
    ☐ Nested task @high

Archive:
  ✔ Old completed task
```

## Supported File Extensions

- `.todo`, `.todos`
- `.task`, `.tasks`
- `.taskpaper`

## Keybindings (Vim Mode)

Add to your `keymap.json`:

```json
[
  {
    "context": "Editor && language == todo && VimControl && !VimWaiting && !menu",
    "bindings": {
      "+": ["workspace::SendKeystrokes", "o ☐ space"]
    }
  }
]
```

## Development

This extension is under active development. Language Server features (toggle done/cancelled, archive) coming soon.

## License

MIT
