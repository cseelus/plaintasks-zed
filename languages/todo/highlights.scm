; Projects - bold headings (using title + emphasis.strong for bold)
; Only style project_name when it's actually in a project node, not in ERROR nodes
(project (project_name) @title)
(project (project_name) @emphasis.strong)

; Task Symbols
(pending_symbol) @function
(done_symbol) @string
(cancelled_symbol) @keyword.exception

; Gray out completed/cancelled task text
(todo_done (task_content) @comment)
(todo_cancelled (task_content) @comment)

; Tags - base styling
(tag_name) @property
(tag_value) @string

; Special priority tags (high priority - red/warning colors)
((tag_name) @keyword
 (#any-of? @keyword "critical" "high" "important"))

; Low priority tags (muted)
((tag_name) @comment.doc
 (#any-of? @comment.doc "low" "maybe" "someday"))

; Today tag (distinct color)
((tag_name) @constant
 (#eq? @constant "today"))

; Time-related tags
((tag_name) @type
 (#any-of? @type "created" "started" "done" "cancelled" "lasted" "est" "medium"))
