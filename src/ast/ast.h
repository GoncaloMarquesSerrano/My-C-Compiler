#ifndef AST_H
#define AST_H

typedef enum {
  CONSTANT,
} ExpressionType;

typedef enum {
  STMT_RETURN,
} StatementType;

typedef struct {
  int value;
} Constant;

typedef struct {
  ExpressionType expression_type;
  union {
    Constant constant;
  };
} Expression;

typedef struct {
  Expression exp;
} ReturnStatement;

typedef struct {
  StatementType statement_type;
  union {
    ReturnStatement ret_stmt;
  };
} Statement;

typedef struct {
  char *identifier;
  Statement body;
} Function;

typedef struct {
  Function function;
} Program;

void program_printer(Program *program, int indent);
void function_printer(Function *function, int indent);
void statement_printer(Statement *statement, int indent);
void expression_printer(Expression *expression, int indent);

#endif // !AST_H
