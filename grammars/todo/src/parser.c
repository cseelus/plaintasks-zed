#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 66
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 31
#define ALIAS_COUNT 0
#define TOKEN_COUNT 15
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 7
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_COLON = 1,
  aux_sym_project_token1 = 2,
  sym_project_name = 3,
  sym_pending_symbol = 4,
  sym_done_symbol = 5,
  sym_cancelled_symbol = 6,
  anon_sym_AT = 7,
  sym_tag_name = 8,
  anon_sym_LPAREN = 9,
  anon_sym_RPAREN = 10,
  sym_tag_value = 11,
  sym_text = 12,
  sym_comment_text = 13,
  aux_sym__eol_token1 = 14,
  sym_document = 15,
  sym_project = 16,
  sym_todo_pending = 17,
  sym_todo_done = 18,
  sym_todo_cancelled = 19,
  sym_task_content = 20,
  sym_tag = 21,
  sym_tag_value_group = 22,
  sym_tags = 23,
  sym_comment = 24,
  sym__indent = 25,
  sym__eol = 26,
  sym_empty_line = 27,
  aux_sym_document_repeat1 = 28,
  aux_sym_task_content_repeat1 = 29,
  aux_sym_tags_repeat1 = 30,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_COLON] = ":",
  [aux_sym_project_token1] = "project_token1",
  [sym_project_name] = "project_name",
  [sym_pending_symbol] = "pending_symbol",
  [sym_done_symbol] = "done_symbol",
  [sym_cancelled_symbol] = "cancelled_symbol",
  [anon_sym_AT] = "@",
  [sym_tag_name] = "tag_name",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_tag_value] = "tag_value",
  [sym_text] = "text",
  [sym_comment_text] = "comment_text",
  [aux_sym__eol_token1] = "_eol_token1",
  [sym_document] = "document",
  [sym_project] = "project",
  [sym_todo_pending] = "todo_pending",
  [sym_todo_done] = "todo_done",
  [sym_todo_cancelled] = "todo_cancelled",
  [sym_task_content] = "task_content",
  [sym_tag] = "tag",
  [sym_tag_value_group] = "tag_value_group",
  [sym_tags] = "tags",
  [sym_comment] = "comment",
  [sym__indent] = "_indent",
  [sym__eol] = "_eol",
  [sym_empty_line] = "empty_line",
  [aux_sym_document_repeat1] = "document_repeat1",
  [aux_sym_task_content_repeat1] = "task_content_repeat1",
  [aux_sym_tags_repeat1] = "tags_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_COLON] = anon_sym_COLON,
  [aux_sym_project_token1] = aux_sym_project_token1,
  [sym_project_name] = sym_project_name,
  [sym_pending_symbol] = sym_pending_symbol,
  [sym_done_symbol] = sym_done_symbol,
  [sym_cancelled_symbol] = sym_cancelled_symbol,
  [anon_sym_AT] = anon_sym_AT,
  [sym_tag_name] = sym_tag_name,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_tag_value] = sym_tag_value,
  [sym_text] = sym_text,
  [sym_comment_text] = sym_comment_text,
  [aux_sym__eol_token1] = aux_sym__eol_token1,
  [sym_document] = sym_document,
  [sym_project] = sym_project,
  [sym_todo_pending] = sym_todo_pending,
  [sym_todo_done] = sym_todo_done,
  [sym_todo_cancelled] = sym_todo_cancelled,
  [sym_task_content] = sym_task_content,
  [sym_tag] = sym_tag,
  [sym_tag_value_group] = sym_tag_value_group,
  [sym_tags] = sym_tags,
  [sym_comment] = sym_comment,
  [sym__indent] = sym__indent,
  [sym__eol] = sym__eol,
  [sym_empty_line] = sym_empty_line,
  [aux_sym_document_repeat1] = aux_sym_document_repeat1,
  [aux_sym_task_content_repeat1] = aux_sym_task_content_repeat1,
  [aux_sym_tags_repeat1] = aux_sym_tags_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_project_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_project_name] = {
    .visible = true,
    .named = true,
  },
  [sym_pending_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_done_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_cancelled_symbol] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_AT] = {
    .visible = true,
    .named = false,
  },
  [sym_tag_name] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_tag_value] = {
    .visible = true,
    .named = true,
  },
  [sym_text] = {
    .visible = true,
    .named = true,
  },
  [sym_comment_text] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__eol_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_document] = {
    .visible = true,
    .named = true,
  },
  [sym_project] = {
    .visible = true,
    .named = true,
  },
  [sym_todo_pending] = {
    .visible = true,
    .named = true,
  },
  [sym_todo_done] = {
    .visible = true,
    .named = true,
  },
  [sym_todo_cancelled] = {
    .visible = true,
    .named = true,
  },
  [sym_task_content] = {
    .visible = true,
    .named = true,
  },
  [sym_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_tag_value_group] = {
    .visible = true,
    .named = true,
  },
  [sym_tags] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym__indent] = {
    .visible = false,
    .named = true,
  },
  [sym__eol] = {
    .visible = false,
    .named = true,
  },
  [sym_empty_line] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_document_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_task_content_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_tags_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 22,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 33,
  [36] = 36,
  [37] = 34,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 61,
  [64] = 56,
  [65] = 58,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(7);
      if (lookahead == '\n') ADVANCE(22);
      if (lookahead == '\r') SKIP(0);
      if (lookahead == '(') ADVANCE(16);
      if (lookahead == ')') ADVANCE(18);
      if (lookahead == ':') ADVANCE(8);
      if (lookahead == '@') ADVANCE(14);
      if (lookahead == 0x2610) ADVANCE(11);
      if (lookahead == 0x2714) ADVANCE(12);
      if (lookahead == 0x2718) ADVANCE(13);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      if (lookahead != 0) ADVANCE(21);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(22);
      if (lookahead == '\r') SKIP(1);
      if (lookahead == '(') ADVANCE(16);
      if (lookahead == ')') ADVANCE(18);
      if (lookahead == ':') ADVANCE(8);
      if (lookahead == '@') ADVANCE(14);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(22);
      if (lookahead == '\r') SKIP(2);
      if (lookahead == '@') ADVANCE(14);
      if (lookahead != 0) ADVANCE(20);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(22);
      if (lookahead == '\r') SKIP(3);
      if (lookahead == '(') ADVANCE(17);
      if (lookahead == '@') ADVANCE(14);
      if (lookahead != 0) ADVANCE(20);
      END_STATE();
    case 4:
      if (lookahead == '\r') SKIP(4);
      if (lookahead == 0x2610) ADVANCE(11);
      if (lookahead == 0x2714) ADVANCE(12);
      if (lookahead == 0x2718) ADVANCE(13);
      if (lookahead == '\t' ||
          lookahead == ' ' ||
          lookahead == ':') ADVANCE(21);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n') ADVANCE(10);
      END_STATE();
    case 5:
      if (lookahead == '\r') SKIP(5);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != ')') ADVANCE(19);
      END_STATE();
    case 6:
      if (eof) ADVANCE(7);
      if (lookahead == '\n') ADVANCE(22);
      if (lookahead == '\r') SKIP(6);
      if (lookahead == ':') ADVANCE(21);
      if (lookahead == 0x2610) ADVANCE(11);
      if (lookahead == 0x2714) ADVANCE(12);
      if (lookahead == 0x2718) ADVANCE(13);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (lookahead != 0) ADVANCE(10);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(aux_sym_project_token1);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym_project_name);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':') ADVANCE(10);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym_pending_symbol);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_done_symbol);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(sym_cancelled_symbol);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(sym_tag_name);
      if (lookahead == '-' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '@') ADVANCE(20);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_tag_value);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ')') ADVANCE(19);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(sym_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '@') ADVANCE(20);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(sym_comment_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(21);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(aux_sym__eol_token1);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 6},
  [2] = {.lex_state = 6},
  [3] = {.lex_state = 6},
  [4] = {.lex_state = 6},
  [5] = {.lex_state = 6},
  [6] = {.lex_state = 6},
  [7] = {.lex_state = 6},
  [8] = {.lex_state = 6},
  [9] = {.lex_state = 6},
  [10] = {.lex_state = 6},
  [11] = {.lex_state = 6},
  [12] = {.lex_state = 6},
  [13] = {.lex_state = 6},
  [14] = {.lex_state = 6},
  [15] = {.lex_state = 6},
  [16] = {.lex_state = 6},
  [17] = {.lex_state = 6},
  [18] = {.lex_state = 1},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 2},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 2},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 4},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 3},
  [30] = {.lex_state = 2},
  [31] = {.lex_state = 2},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 1},
  [34] = {.lex_state = 1},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 1},
  [57] = {.lex_state = 1},
  [58] = {.lex_state = 5},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 1},
  [62] = {.lex_state = 1},
  [63] = {.lex_state = 1},
  [64] = {.lex_state = 1},
  [65] = {.lex_state = 5},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [aux_sym_project_token1] = ACTIONS(1),
    [sym_pending_symbol] = ACTIONS(1),
    [sym_done_symbol] = ACTIONS(1),
    [sym_cancelled_symbol] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
    [sym_tag_name] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_comment_text] = ACTIONS(1),
    [aux_sym__eol_token1] = ACTIONS(1),
  },
  [1] = {
    [sym_document] = STATE(52),
    [sym_project] = STATE(2),
    [sym_todo_pending] = STATE(2),
    [sym_todo_done] = STATE(2),
    [sym_todo_cancelled] = STATE(2),
    [sym_comment] = STATE(2),
    [sym__indent] = STATE(27),
    [sym_empty_line] = STATE(2),
    [aux_sym_document_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [aux_sym_project_token1] = ACTIONS(5),
    [sym_project_name] = ACTIONS(7),
    [sym_pending_symbol] = ACTIONS(9),
    [sym_done_symbol] = ACTIONS(11),
    [sym_cancelled_symbol] = ACTIONS(13),
    [sym_comment_text] = ACTIONS(15),
    [aux_sym__eol_token1] = ACTIONS(17),
  },
  [2] = {
    [sym_project] = STATE(3),
    [sym_todo_pending] = STATE(3),
    [sym_todo_done] = STATE(3),
    [sym_todo_cancelled] = STATE(3),
    [sym_comment] = STATE(3),
    [sym__indent] = STATE(27),
    [sym_empty_line] = STATE(3),
    [aux_sym_document_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(19),
    [aux_sym_project_token1] = ACTIONS(5),
    [sym_project_name] = ACTIONS(7),
    [sym_pending_symbol] = ACTIONS(9),
    [sym_done_symbol] = ACTIONS(11),
    [sym_cancelled_symbol] = ACTIONS(13),
    [sym_comment_text] = ACTIONS(15),
    [aux_sym__eol_token1] = ACTIONS(17),
  },
  [3] = {
    [sym_project] = STATE(3),
    [sym_todo_pending] = STATE(3),
    [sym_todo_done] = STATE(3),
    [sym_todo_cancelled] = STATE(3),
    [sym_comment] = STATE(3),
    [sym__indent] = STATE(27),
    [sym_empty_line] = STATE(3),
    [aux_sym_document_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(21),
    [aux_sym_project_token1] = ACTIONS(23),
    [sym_project_name] = ACTIONS(26),
    [sym_pending_symbol] = ACTIONS(29),
    [sym_done_symbol] = ACTIONS(32),
    [sym_cancelled_symbol] = ACTIONS(35),
    [sym_comment_text] = ACTIONS(38),
    [aux_sym__eol_token1] = ACTIONS(41),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 2,
    ACTIONS(46), 1,
      sym_comment_text,
    ACTIONS(44), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [13] = 2,
    ACTIONS(50), 1,
      sym_comment_text,
    ACTIONS(48), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [26] = 2,
    ACTIONS(54), 1,
      sym_comment_text,
    ACTIONS(52), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [39] = 2,
    ACTIONS(58), 1,
      sym_comment_text,
    ACTIONS(56), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [52] = 2,
    ACTIONS(62), 1,
      sym_comment_text,
    ACTIONS(60), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [65] = 2,
    ACTIONS(66), 1,
      sym_comment_text,
    ACTIONS(64), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [78] = 2,
    ACTIONS(70), 1,
      sym_comment_text,
    ACTIONS(68), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [91] = 2,
    ACTIONS(74), 1,
      sym_comment_text,
    ACTIONS(72), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [104] = 2,
    ACTIONS(78), 1,
      sym_comment_text,
    ACTIONS(76), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [117] = 2,
    ACTIONS(82), 1,
      sym_comment_text,
    ACTIONS(80), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [130] = 2,
    ACTIONS(86), 1,
      sym_comment_text,
    ACTIONS(84), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [143] = 2,
    ACTIONS(90), 1,
      sym_comment_text,
    ACTIONS(88), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [156] = 2,
    ACTIONS(94), 1,
      sym_comment_text,
    ACTIONS(92), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [169] = 2,
    ACTIONS(98), 1,
      sym_comment_text,
    ACTIONS(96), 7,
      ts_builtin_sym_end,
      aux_sym_project_token1,
      sym_project_name,
      sym_pending_symbol,
      sym_done_symbol,
      sym_cancelled_symbol,
      aux_sym__eol_token1,
  [182] = 5,
    ACTIONS(100), 1,
      anon_sym_AT,
    ACTIONS(102), 1,
      aux_sym__eol_token1,
    STATE(11), 1,
      sym__eol,
    STATE(36), 1,
      sym_tags,
    STATE(28), 2,
      sym_tag,
      aux_sym_tags_repeat1,
  [199] = 5,
    ACTIONS(100), 1,
      anon_sym_AT,
    ACTIONS(104), 1,
      aux_sym__eol_token1,
    STATE(16), 1,
      sym__eol,
    STATE(39), 1,
      sym_tags,
    STATE(28), 2,
      sym_tag,
      aux_sym_tags_repeat1,
  [216] = 3,
    ACTIONS(108), 1,
      anon_sym_AT,
    ACTIONS(106), 2,
      aux_sym_project_token1,
      aux_sym__eol_token1,
    STATE(20), 2,
      sym_tag,
      aux_sym_tags_repeat1,
  [228] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(113), 1,
      sym_text,
    STATE(48), 1,
      sym_task_content,
    STATE(23), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [242] = 3,
    ACTIONS(117), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_tag_value_group,
    ACTIONS(115), 3,
      aux_sym_project_token1,
      anon_sym_AT,
      aux_sym__eol_token1,
  [254] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(119), 1,
      sym_text,
    ACTIONS(121), 1,
      aux_sym__eol_token1,
    STATE(31), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [268] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(113), 1,
      sym_text,
    STATE(41), 1,
      sym_task_content,
    STATE(23), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [282] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(113), 1,
      sym_text,
    STATE(44), 1,
      sym_task_content,
    STATE(23), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [296] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(113), 1,
      sym_text,
    STATE(45), 1,
      sym_task_content,
    STATE(23), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [310] = 5,
    ACTIONS(123), 1,
      sym_project_name,
    ACTIONS(125), 1,
      sym_pending_symbol,
    ACTIONS(127), 1,
      sym_done_symbol,
    ACTIONS(129), 1,
      sym_cancelled_symbol,
    ACTIONS(131), 1,
      sym_comment_text,
  [326] = 3,
    ACTIONS(100), 1,
      anon_sym_AT,
    ACTIONS(133), 2,
      aux_sym_project_token1,
      aux_sym__eol_token1,
    STATE(20), 2,
      sym_tag,
      aux_sym_tags_repeat1,
  [338] = 4,
    ACTIONS(135), 1,
      anon_sym_LPAREN,
    ACTIONS(137), 1,
      sym_text,
    STATE(37), 1,
      sym_tag_value_group,
    ACTIONS(115), 2,
      anon_sym_AT,
      aux_sym__eol_token1,
  [352] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(113), 1,
      sym_text,
    STATE(47), 1,
      sym_task_content,
    STATE(23), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [366] = 4,
    ACTIONS(139), 1,
      anon_sym_AT,
    ACTIONS(142), 1,
      sym_text,
    ACTIONS(145), 1,
      aux_sym__eol_token1,
    STATE(31), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [380] = 4,
    ACTIONS(111), 1,
      anon_sym_AT,
    ACTIONS(113), 1,
      sym_text,
    STATE(42), 1,
      sym_task_content,
    STATE(23), 2,
      sym_tag,
      aux_sym_task_content_repeat1,
  [394] = 1,
    ACTIONS(147), 3,
      aux_sym_project_token1,
      anon_sym_AT,
      aux_sym__eol_token1,
  [400] = 1,
    ACTIONS(149), 3,
      aux_sym_project_token1,
      anon_sym_AT,
      aux_sym__eol_token1,
  [406] = 1,
    ACTIONS(147), 3,
      anon_sym_AT,
      sym_text,
      aux_sym__eol_token1,
  [412] = 3,
    ACTIONS(151), 1,
      aux_sym_project_token1,
    ACTIONS(153), 1,
      aux_sym__eol_token1,
    STATE(6), 1,
      sym__eol,
  [422] = 1,
    ACTIONS(149), 3,
      anon_sym_AT,
      sym_text,
      aux_sym__eol_token1,
  [428] = 3,
    ACTIONS(104), 1,
      aux_sym__eol_token1,
    ACTIONS(155), 1,
      aux_sym_project_token1,
    STATE(16), 1,
      sym__eol,
  [438] = 3,
    ACTIONS(102), 1,
      aux_sym__eol_token1,
    ACTIONS(157), 1,
      aux_sym_project_token1,
    STATE(11), 1,
      sym__eol,
  [448] = 3,
    ACTIONS(159), 1,
      aux_sym_project_token1,
    ACTIONS(161), 1,
      aux_sym__eol_token1,
    STATE(4), 1,
      sym__eol,
  [458] = 2,
    ACTIONS(163), 1,
      aux_sym__eol_token1,
    STATE(9), 1,
      sym__eol,
  [465] = 2,
    ACTIONS(165), 1,
      aux_sym__eol_token1,
    STATE(12), 1,
      sym__eol,
  [472] = 2,
    ACTIONS(167), 1,
      aux_sym__eol_token1,
    STATE(17), 1,
      sym__eol,
  [479] = 2,
    ACTIONS(169), 1,
      aux_sym__eol_token1,
    STATE(8), 1,
      sym__eol,
  [486] = 2,
    ACTIONS(171), 1,
      aux_sym__eol_token1,
    STATE(7), 1,
      sym__eol,
  [493] = 2,
    ACTIONS(153), 1,
      aux_sym__eol_token1,
    STATE(6), 1,
      sym__eol,
  [500] = 2,
    ACTIONS(173), 1,
      aux_sym__eol_token1,
    STATE(14), 1,
      sym__eol,
  [507] = 2,
    ACTIONS(175), 1,
      aux_sym__eol_token1,
    STATE(13), 1,
      sym__eol,
  [514] = 2,
    ACTIONS(177), 1,
      aux_sym__eol_token1,
    STATE(5), 1,
      sym__eol,
  [521] = 2,
    ACTIONS(179), 1,
      aux_sym__eol_token1,
    STATE(15), 1,
      sym__eol,
  [528] = 1,
    ACTIONS(181), 1,
      aux_sym_project_token1,
  [532] = 1,
    ACTIONS(183), 1,
      ts_builtin_sym_end,
  [536] = 1,
    ACTIONS(185), 1,
      aux_sym_project_token1,
  [540] = 1,
    ACTIONS(187), 1,
      aux_sym_project_token1,
  [544] = 1,
    ACTIONS(189), 1,
      aux_sym_project_token1,
  [548] = 1,
    ACTIONS(191), 1,
      anon_sym_RPAREN,
  [552] = 1,
    ACTIONS(193), 1,
      anon_sym_COLON,
  [556] = 1,
    ACTIONS(195), 1,
      sym_tag_value,
  [560] = 1,
    ACTIONS(197), 1,
      aux_sym_project_token1,
  [564] = 1,
    ACTIONS(199), 1,
      aux_sym_project_token1,
  [568] = 1,
    ACTIONS(201), 1,
      sym_tag_name,
  [572] = 1,
    ACTIONS(203), 1,
      anon_sym_COLON,
  [576] = 1,
    ACTIONS(205), 1,
      sym_tag_name,
  [580] = 1,
    ACTIONS(207), 1,
      anon_sym_RPAREN,
  [584] = 1,
    ACTIONS(209), 1,
      sym_tag_value,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 13,
  [SMALL_STATE(6)] = 26,
  [SMALL_STATE(7)] = 39,
  [SMALL_STATE(8)] = 52,
  [SMALL_STATE(9)] = 65,
  [SMALL_STATE(10)] = 78,
  [SMALL_STATE(11)] = 91,
  [SMALL_STATE(12)] = 104,
  [SMALL_STATE(13)] = 117,
  [SMALL_STATE(14)] = 130,
  [SMALL_STATE(15)] = 143,
  [SMALL_STATE(16)] = 156,
  [SMALL_STATE(17)] = 169,
  [SMALL_STATE(18)] = 182,
  [SMALL_STATE(19)] = 199,
  [SMALL_STATE(20)] = 216,
  [SMALL_STATE(21)] = 228,
  [SMALL_STATE(22)] = 242,
  [SMALL_STATE(23)] = 254,
  [SMALL_STATE(24)] = 268,
  [SMALL_STATE(25)] = 282,
  [SMALL_STATE(26)] = 296,
  [SMALL_STATE(27)] = 310,
  [SMALL_STATE(28)] = 326,
  [SMALL_STATE(29)] = 338,
  [SMALL_STATE(30)] = 352,
  [SMALL_STATE(31)] = 366,
  [SMALL_STATE(32)] = 380,
  [SMALL_STATE(33)] = 394,
  [SMALL_STATE(34)] = 400,
  [SMALL_STATE(35)] = 406,
  [SMALL_STATE(36)] = 412,
  [SMALL_STATE(37)] = 422,
  [SMALL_STATE(38)] = 428,
  [SMALL_STATE(39)] = 438,
  [SMALL_STATE(40)] = 448,
  [SMALL_STATE(41)] = 458,
  [SMALL_STATE(42)] = 465,
  [SMALL_STATE(43)] = 472,
  [SMALL_STATE(44)] = 479,
  [SMALL_STATE(45)] = 486,
  [SMALL_STATE(46)] = 493,
  [SMALL_STATE(47)] = 500,
  [SMALL_STATE(48)] = 507,
  [SMALL_STATE(49)] = 514,
  [SMALL_STATE(50)] = 521,
  [SMALL_STATE(51)] = 528,
  [SMALL_STATE(52)] = 532,
  [SMALL_STATE(53)] = 536,
  [SMALL_STATE(54)] = 540,
  [SMALL_STATE(55)] = 544,
  [SMALL_STATE(56)] = 548,
  [SMALL_STATE(57)] = 552,
  [SMALL_STATE(58)] = 556,
  [SMALL_STATE(59)] = 560,
  [SMALL_STATE(60)] = 564,
  [SMALL_STATE(61)] = 568,
  [SMALL_STATE(62)] = 572,
  [SMALL_STATE(63)] = 576,
  [SMALL_STATE(64)] = 580,
  [SMALL_STATE(65)] = 584,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1, 0, 0),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0),
  [23] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(27),
  [26] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(59),
  [32] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(55),
  [35] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(54),
  [38] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(50),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(10),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 3, 0, 0),
  [46] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_project, 3, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 7, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_project, 7, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 6, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_project, 6, 0, 0),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_cancelled, 5, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_cancelled, 5, 0, 0),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_done, 5, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_done, 5, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_pending, 5, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_pending, 5, 0, 0),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_empty_line, 1, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_empty_line, 1, 0, 0),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 5, 0, 0),
  [74] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_project, 5, 0, 0),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_cancelled, 4, 0, 0),
  [78] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_cancelled, 4, 0, 0),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_done, 4, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_done, 4, 0, 0),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_pending, 4, 0, 0),
  [86] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_pending, 4, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 2, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment, 2, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_project, 4, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_project, 4, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 3, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment, 3, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_tags_repeat1, 2, 0, 0),
  [108] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_tags_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tag, 2, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_task_content, 1, 0, 0),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tags, 1, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [137] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_tag, 2, 0, 0),
  [139] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_task_content_repeat1, 2, 0, 0), SHIFT_REPEAT(61),
  [142] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_task_content_repeat1, 2, 0, 0), SHIFT_REPEAT(31),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_task_content_repeat1, 2, 0, 0),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tag_value_group, 3, 0, 0),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tag, 3, 0, 0),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [183] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_todo(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
