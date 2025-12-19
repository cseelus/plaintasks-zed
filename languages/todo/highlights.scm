; Projects - heading style
(project) @markup.heading
(project_name) @markup.heading

; Pending todos
(pending_symbol) @punctuation.special

; Done todos - muted appearance
(done_symbol) @string.special
(todo_done (task_content) @comment)

; Cancelled todos
(cancelled_symbol) @constant
(todo_cancelled (task_content) @comment)

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
(comment_text) @comment
