#include "../ast/ast.h"
#include "../lexer/lexer.h"

#ifndef PARSER_H
#define PARSER_H

void parse_program(Program *program, TokenList *list);

#endif // !PARSER_H
