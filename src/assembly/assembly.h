#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <cstddef>
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
  char *identifier;
  Instruction *instructions;
} FunctionDefinition;

typedef struct {
  FunctionDefinition function_definition;
} Program;

typedef struct {
  Instruction *instructions;
  size_t size;
  size_t capacity;
} InstructionList;

#endif // !ASSEMBLY_H
