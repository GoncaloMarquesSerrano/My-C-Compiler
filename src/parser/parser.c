#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

static void parse_expression(Expression *expression, TokenList *list,
                             size_t *pos) {
  Token *current_token = &list->tokens[*pos];
  verify_expected_token(TOKEN_CONSTANT, list, pos);
  int token_value = atoi(current_token->value);
  expression->expression_type = CONSTANT;
  expression->constant.value = token_value;
}

static void parse_statement(Statement *statement, TokenList *list,
                            size_t *pos) {
  verify_expected_token(TOKEN_RETURN, list, pos);
  statement->statement_type = STMT_RETURN;
  parse_expression(&statement->ret_stmt.exp, list, pos);
  verify_expected_token(TOKEN_SEMICOLON, list, pos);
}

static void parse_function(Function *function, TokenList *list, size_t *pos) {
  verify_expected_token(TOKEN_INT, list, pos);
  function->identifier = list->tokens[*pos].value;
  verify_expected_token(TOKEN_IDENTIFIER, list, pos);
  verify_expected_token(TOKEN_LPAREN, list, pos);
  verify_expected_token(TOKEN_VOID, list, pos);
  verify_expected_token(TOKEN_RPAREN, list, pos);
  verify_expected_token(TOKEN_LBRACE, list, pos);
  parse_statement(&function->body, list, pos);
  verify_expected_token(TOKEN_RBRACE, list, pos);
}

void parse_program(Program *program, TokenList *list) {
  size_t pos = 0;
  parse_function(&program->function, list, &pos);
  verify_expected_token(TOKEN_EOF, list, &pos);
}
