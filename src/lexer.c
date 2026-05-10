#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TokenList token_list_init() {
  TokenList list;

  list.tokens = malloc(16 * sizeof(Token));
  if (list.tokens == NULL) {
    fprintf(stderr, "Error allocating memory for tokens\n");
    exit(1);
  }

  list.capacity = 16;
  list.size = 0;

  return list;
}

void token_list_push(Token token, TokenList *list) {
  if (list->size >= list->capacity) {
    size_t new_capacity = list->capacity * 2;

    Token *new_tokens = realloc(list->tokens, new_capacity * sizeof(Token));

    if (new_tokens == NULL) {
      fprintf(stderr, "Error reallocating tokens\n");
      exit(1);
    }

    list->tokens = new_tokens;
    list->capacity = new_capacity;
  }

  list->tokens[list->size] = token;
  list->size++;
}

void token_list_free(TokenList *list) {
  if (list == NULL || list->tokens == NULL) {
    return;
  }

  for (size_t i = 0; i < list->size; i++) {
    free(list->tokens[i].value);
  }

  free(list->tokens);

  list->tokens = NULL;
  list->size = 0;
  list->capacity = 0;
}
