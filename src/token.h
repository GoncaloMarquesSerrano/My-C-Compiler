#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  TOKEN_INT,
  TOKEN_VOID,
  TOKEN_RETURN,
  TOKEN_IDENTIFIER,
  TOKEN_CONSTANT,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_SEMICOLON,
  TOKEN_EOF
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

#endif // !TOKEN_H
