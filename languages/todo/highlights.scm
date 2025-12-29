; Projects
(project_name) @markup.heading

; Symbols
(pending_symbol) @punctuation.special
(done_symbol) @string.special
(cancelled_symbol) @keyword.operator

; Tags
(tag) @tag

; Comments
(comment) @comment

; Text
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
(comment) @comment
