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
  char *value; /* Heap-allocated (strdup). NULL for tokens with no
                  semantic value (keywords, punctuation). Caller must
                  use token_list_free() to release. */
} Token;

char *token_type_to_string(TokenType token_type);

#endif // !TOKEN_H
