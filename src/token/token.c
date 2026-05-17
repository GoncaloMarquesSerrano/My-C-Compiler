#include "token.h"

char *token_type_to_string(TokenType token_type) {
  switch (token_type) {
  case TOKEN_INT:
    return "Integer";
  case TOKEN_VOID:
    return "Void";
  case TOKEN_RETURN:
    return "Return";
  case TOKEN_IDENTIFIER:
    return "Identifier";
  case TOKEN_CONSTANT:
    return "Constant";
  case TOKEN_LPAREN:
    return "(";
  case TOKEN_RPAREN:
    return ")";
  case TOKEN_LBRACE:
    return "{";
  case TOKEN_RBRACE:
    return "}";
  case TOKEN_SEMICOLON:
    return ";";
  case TOKEN_EOF:
    return "EOF";
  default:
    return "Unkown";
  }
}
