#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void parse_program(Program *program, TokenList *list) {}

static void parse_function(Function *function, TokenList *list, size_t *pos) {}

static void parse_statement(Statement *statement, TokenList *list,
                            size_t *pos) {}

static void parse_expression(Expression *expression, TokenList *list,
                             size_t *pos) {}

static void verify_expected_token(TokenType expected_token_type,
                                  TokenList *list, size_t *pos) {
  Token current_token = list->tokens[*pos];

  if (current_token.type != expected_token_type) {
    fprintf(stderr, "Expected %s but found %s",
            token_type_to_string(expected_token_type),
            token_type_to_string(current_token.type));
    exit(1);
  };

  (*pos)++;
}
