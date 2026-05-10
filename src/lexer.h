#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stddef.h>

typedef struct {
  Token *tokens;
  size_t size;
  size_t capacity;
} TokenList;

TokenList lexer_tokenize(const char *src);
void token_list_free(TokenList *list);

#endif // !LEXER_H
