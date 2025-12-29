# PlainTasks for Zed

A Zed extension for managing todo lists with syntax highlighting. Inspired by [Todo+](https://github.com/fabiospampinato/vscode-todo-plus) for VSCode and [PlainTasks](https://github.com/aziz/PlainTasks) for Sublime Text.

## Features

- Syntax highlighting for `.todo`, `.tasks`, and `.taskpaper` files
- Project headers (lines ending with `:`) displayed in bold
- Task states: pending (`☐`), done (`✔`), cancelled (`✘`)
- Tag support with special colors for priority tags (`@critical`, `@high`, `@today`, `@low`)
- Time-related tags (`@done(timestamp)`, `@cancelled(timestamp)`, `@est(duration)`)
- Comments displayed in italic

## Screenshot

![PlainTasks screenshot](https://github.com/cseelus/plaintasks-zed/blob/main/screenshot.png)

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
  ✔ Old completed task @done(25-01-17 09:00)
```

## Supported File Extensions

- `.todo`, `.todos`
- `.task`, `.tasks`
- `.taskpaper`

## Installation

Search for "PlainTasks" in the Zed extensions panel, or install via the command line:

```bash
zed --install-extension plaintasks
```

## Keybindings

You can add custom keybindings for quick task entry. Add to your `keymap.json`:

```json
[
  {
    "context": "Editor && language == todo",
    "bindings": {
      "alt-enter": ["workspace::SendKeystrokes", "o ☐ space"]
    }
  }
]
```

### Vim Mode

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

## Roadmap

- [ ] Language Server for toggle actions (mark done/cancelled)
- [ ] Archive functionality
- [ ] Tag autocompletion

## License

MIT
