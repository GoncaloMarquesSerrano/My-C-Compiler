#include "file_reader.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char *read_file(const char *file_name, uint64_t *file_size) {
  FILE *fptr;

  fptr = fopen(file_name, "rb");

  if (fptr == NULL) {
    fprintf(stderr, "Could not open file\n");
    return NULL;
  }

  // Goes to the end of the file
  fseek(fptr, 0, SEEK_END);

  // Get current position i.e size
  *file_size = ftell(fptr);

  // Goes back to the beggining
  fseek(fptr, 0, SEEK_SET);

  // Allocates memory according to the file size
  unsigned char *buffer = malloc(*file_size + 1);

  if (buffer == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(fptr);
    return NULL;
  }

  fread(buffer, 1, *file_size, fptr);

  buffer[*file_size] = '\0';

  fclose(fptr);

  return buffer;
}
