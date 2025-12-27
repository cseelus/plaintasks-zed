package tree_sitter_todo_test

import (
	"testing"

	tree_sitter "github.com/smacker/go-tree-sitter"
	"github.com/tree-sitter/tree-sitter-todo"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_todo.Language())
	if language == nil {
		t.Errorf("Error loading Todo grammar")
	}
}
