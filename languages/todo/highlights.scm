; Projects - heading style (bold)
(project_label) @markup.heading.1

; Pending todos
(todo_line) @text

; Todo symbols with specific colors
(todo_symbol) @punctuation.special

; Completed tasks - green symbol
((todo_symbol) @string
 (#eq? @todo_symbol "✔"))

; Cancelled tasks - red symbol
((todo_symbol) @keyword.operator
 (#eq? @todo_symbol "✘"))

; Task content and text
(task_content) @text
(text) @text

; Tags
(tag) @text
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

; Comments
(comment_line) @comment
