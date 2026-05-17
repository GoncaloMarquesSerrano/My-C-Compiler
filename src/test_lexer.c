#include "./token/token.h"
#include "lexer/lexer.h"
#include <stdio.h>

int main(void) {
  TokenList list = lexer_tokenize("int main(void) { return 2; }");

  for (size_t i = 0; i < list.size; i++) {
    Token t = list.tokens[i];
    printf("type=%d value=%s\n", t.type, t.value ? t.value : "(null)");
  }

  token_list_free(&list);
  return 0;
}
