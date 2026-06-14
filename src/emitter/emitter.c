#include "../assembly/assembly.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void emit_operand(const Operand *operand, FILE *file) {
    char buf[32];
    format_operand(operand, buf, sizeof(buf));
    fprintf(file, "%s", buf);
}

void emit_instruction(const Instruction *instruction, FILE *file) {
    switch (instruction->instruction_type) {
    case MOV_INSTRUCTION:
        fprintf(file, "\tmovl ");
        emit_operand(&instruction->mov_instruction.src, file);
        fprintf(file, ", ");
        emit_operand(&instruction->mov_instruction.dst, file);
        fprintf(file, "\n");
        break;

    case RET_INSTRUCTION:
        fprintf(file, "\tret\n");
        break;
    }
}

void emit_function(FunctionDefinition *function, FILE *file) {
  fprintf(file, "\t.globl %s\n%s:\n", function->identifier, function->identifier);
  for (size_t i = 0; i < function->instructions.size; i++) {
    emit_instruction(&function->instructions.instructions[i], file);
  }
}

void emit_program(AssemblyProgram *program, const char *output_path) {
  FILE *fptr;

  fptr = fopen(output_path, "w");

  if (fptr == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(1);
  }

  emit_function(&program->function_definition, fptr);
  fprintf(fptr, "\n.section .note.GNU-stack,\"\",@progbits\n");

  fclose(fptr);
}
