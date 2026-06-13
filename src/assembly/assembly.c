#include "assembly.h"
#include "../ast/ast.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static InstructionList instruction_list_init() {
  InstructionList list;

  list.instructions = malloc(16 * sizeof(Instruction));
  if (list.instructions == NULL) {
    fprintf(stderr, "Error allocating memory for instructions\n");
    exit(1);
  }

  list.capacity = 16;
  list.size = 0;

  return list;
}

static void instruction_list_push(Instruction instruction,
                                  InstructionList *list) {
  if (list->size >= list->capacity) {
    size_t new_capacity = list->capacity * 2;

    Instruction *new_instructions =
        realloc(list->instructions, new_capacity * sizeof(Instruction));

    if (new_instructions == NULL) {
      fprintf(stderr, "Error reallocating instructions\n");
      exit(1);
    }

    list->instructions = new_instructions;
    list->capacity = new_capacity;
  }

  list->instructions[list->size] = instruction;
  list->size++;
}

void instruction_list_free(InstructionList *list) {
  if (list == NULL || list->instructions == NULL) {
    return;
  }

  free(list->instructions);

  list->instructions = NULL;
  list->capacity = 0;
  list->size = 0;
}

static const char *register_to_string(RegisterName reg) {
  switch (reg) {
  case EAX:
    return "eax";
  case EBX:
    return "ebx";
  case ECX:
    return "ecx";
  case EDX:
    return "edx";
  case ESI:
    return "esi";
  case EDI:
    return "edi";
  case ESP:
    return "esp";
  case EBP:
    return "ebp";
  default:
    return "unknown";
  }
}

static void print_operand(const Operand *operand) {
  switch (operand->operand_type) {
  case IMM_OPERAND:
    printf("%d", operand->imm_operand.value);
    break;

  case REGISTER_OPERAND:
    printf("%s",
           register_to_string(operand->register_operand.register_operand));
    break;
  }
}

void instruction_pretty_printer(const Instruction *instruction) {
  switch (instruction->instruction_type) {
  case MOV_INSTRUCTION:
    printf("mov ");
    print_operand(&instruction->mov_instruction.src);
    printf(", ");
    print_operand(&instruction->mov_instruction.dst);
    printf("\n");
    break;

  case RET_INSTRUCTION:
    printf("ret\n");
    break;
  }
}

static Operand make_imm(int v) {
    Operand op;
    op.operand_type = IMM_OPERAND;
    op.imm_operand.value = v;
    return op;
}

static Operand make_reg(RegisterName r) {
    Operand op;
    op.operand_type = REGISTER_OPERAND;
    op.register_operand.register_operand = r;
    return op;
}

static Instruction make_mov(RegisterName dst, Operand src) {
  Instruction instr;

  instr.instruction_type = MOV_INSTRUCTION;

  instr.mov_instruction.dst = make_reg(dst);
  instr.mov_instruction.src = src;

  return instr;
}

static Operand generate_expression(Expression *expression) {
  if (expression->expression_type != CONSTANT) {
    fprintf(stderr, "Different expressions aren't currently supported");
    exit(1);
  }

  return make_imm(expression->constant.value);
}

static void generate_statement(Statement *statement, InstructionList *list){
  if (statement->statement_type == STMT_RETURN) {
    Instruction mov_instruction = make_mov(EAX, generate_expression(&statement->ret_stmt.exp));
    instruction_list_push(mov_instruction, list);
    Instruction ret_instruction;
    ret_instruction.instruction_type = RET_INSTRUCTION;
    instruction_list_push(ret_instruction, list);
  }
}

static FunctionDefinition generate_function(Function *function) {
  FunctionDefinition assembly_function;
  assembly_function.instructions = instruction_list_init();
  assembly_function.identifier = function->identifier;
  generate_statement(&function->body, &assembly_function.instructions);
  return assembly_function;
}

AssemblyProgram generate_program(Program *program) {
  AssemblyProgram assembly_program;
  assembly_program.function_definition = generate_function(&program->function);
  return assembly_program;
}
