#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <stddef.h>
typedef enum { MOV_INSTRUCTION, RET_INSTRUCTION } InstructionType;

typedef enum {
  EAX,
  EBX,
  ECX,
  EDX,
  ESI,
  EDI,
  ESP,
  EBP,
} RegisterName;

typedef enum {
  IMM_OPERAND,
  REGISTER_OPERAND,
} OperandType;

typedef struct {
  int value;
} ImmOperand;

typedef struct {
  RegisterName register_operand;
} RegisterOperand;

typedef struct {
  OperandType operand_type;
  union {
    ImmOperand imm_operand;
    RegisterOperand register_operand;
  };
} Operand;

typedef struct {
  Operand src;
  Operand dst;
} MovInstruction;

typedef struct {
  InstructionType instruction_type;
  union {
    MovInstruction mov_instruction;
  };
} Instruction;

typedef struct {
  Instruction *instructions;
  size_t size;
  size_t capacity;
} InstructionList;

typedef struct {
  char *identifier;
  InstructionList instructions;
} FunctionDefinition;

typedef struct {
  FunctionDefinition function_definition;
} AssemblyProgram;

void instruction_list_free(InstructionList *list);
void instruction_pretty_printer(const Instruction *instruction);

#endif // !ASSEMBLY_H
