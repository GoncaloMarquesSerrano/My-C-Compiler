#include "lexer.h"
#include "token.h"
#include <ctype.h>
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

TokenList lexer_tokenize(const char *src) {
  TokenList list = token_list_init();
  size_t pos = 0;
  while (src[pos] != '\0') {
    Token token;
    if (isspace((unsigned char)src[pos])) {
      pos++;
      continue;
    }

    if (isalpha((unsigned char)src[pos]) || src[pos] == '_') {
      token = (Token){TOKEN_IDENTIFIER, NULL};
      size_t start = pos;

      while (isalnum((unsigned char)src[pos]) || src[pos] == '_') {
        pos++;
      }

      token.value = strndup(src + start, pos - start);

      if (strcmp(token.value, "int") == 0) {
        token.type = TOKEN_INT;
        free(token.value);
        token.value = NULL;
      } else if (strcmp(token.value, "void") == 0) {
        token.type = TOKEN_VOID;
        free(token.value);
        token.value = NULL;
      } else if (strcmp(token.value, "return") == 0) {
        token.type = TOKEN_RETURN;
        free(token.value);
        token.value = NULL;
      }

    } else if (isdigit((unsigned char)src[pos])) {

      token = (Token){TOKEN_CONSTANT, NULL};

      size_t start = pos;
      while (isdigit(src[pos])) {
        pos++;
      }

      if (isalpha((unsigned char)src[pos]) || src[pos] == '_') {
        fprintf(stderr, "Invalid token at position %zu\n", pos);
        exit(1);
      }

      token.value = strndup(src + start, pos - start);

    } else {
      switch (src[pos]) {
      case '(':
        token = (Token){TOKEN_LPAREN, NULL};
        pos++;
        break;
      case ')':
        token = (Token){TOKEN_RPAREN, NULL};
        pos++;
        break;
      case '{':
        token = (Token){TOKEN_LBRACE, NULL};
        pos++;
        break;
      case '}':
        token = (Token){TOKEN_RBRACE, NULL};
        pos++;
        break;
      case ';':
        token = (Token){TOKEN_SEMICOLON, NULL};
        pos++;
        break;

      default:
        fprintf(stderr, "Unexpected character: %c:\n", src[pos]);
        exit(1);
      }
    }
    token_list_push(token, &list);
  }
  token_list_push((Token){TOKEN_EOF, NULL}, &list);
  return list;
}
