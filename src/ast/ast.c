#include "ast.h"
#include <stdio.h>

static void print_indent(int indent) {
  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
}

void program_printer(Program *program, int indent) {
  print_indent(indent);
  printf("Program(\n");

  function_printer(&program->function, indent + 1);

  print_indent(indent);
  printf(")\n");
}

void function_printer(Function *function, int indent) {
  print_indent(indent);
  printf("Function(name=%s,\n", function->identifier);

  print_indent(indent);
  printf("body=\n");

  statement_printer(&function->body, indent + 1);

  print_indent(indent);
  printf(")\n");
}

void statement_printer(Statement *statement, int indent) {
  switch (statement->statement_type) {
  case STMT_RETURN:
    print_indent(indent);
    printf("Return(\n");

    expression_printer(&statement->ret_stmt.exp, indent + 1);

    print_indent(indent);
    printf(")\n");
    break;

  default:
    print_indent(indent);
    printf("Unknown\n");
  }
}

void expression_printer(Expression *expression, int indent) {
  switch (expression->expression_type) {
  case CONSTANT:
    print_indent(indent);
    printf("Constant(%u)\n", expression->constant.value);
    break;

  default:
    print_indent(indent);
    printf("Unknown\n");
  }
}
