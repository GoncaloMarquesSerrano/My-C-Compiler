#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void build_filenames(const char *input, char *preprocessed, char *assembly,
                     char *executable, size_t buf_size) {
  char *pos = strrchr(input, '.');

  if (pos == NULL) {
    fprintf(stderr, "No extension found\n");
    exit(1);
  }

  size_t len = pos - input;

  char filename[512];

  strncpy(filename, input, len);
  filename[len] = '\0';

  snprintf(preprocessed, buf_size, "%s.i", filename);
  snprintf(assembly, buf_size, "%s.s", filename);
  snprintf(executable, buf_size, "%s", filename);
}

int run_compiler(const char *input_file, const char *flag) {
  char preprocessed[512], assembly[512], executable[512];
  build_filenames(input_file, preprocessed, assembly, executable, 512);

  // step 1: preprocess
  char cmd[1024];
  snprintf(cmd, sizeof(cmd), "gcc -E -P %s -o %s", input_file, preprocessed);
  if (system(cmd) != 0) {
    fprintf(stderr, "Error preprocessing file\n");
    return 1;
  }

  // step 2: compile
  // stubbing out for now

  printf("Compiling...");

  // if any flag is given doesnt do anything
  if (strlen(flag) > 0) {
    if (remove(preprocessed) != 0)
      fprintf(stderr, "Error deleting preprocessed file\n");
    return 0;
  }

  if (remove(preprocessed) != 0) {
    fprintf(stderr, "Error deleting preprocessed file\n");
    return 1;
  }

  // step 3: assemble and link to produce executable
  /*
  snprintf(cmd, sizeof(cmd), "gcc %s -o %s", assembly, executable);
  if (system(cmd) != 0) {
    fprintf(stderr, "Error linking assembly file");
    return 1;
  }
  */
  remove(assembly);
  return 0;
}

int main(int argc, char *argv[]) {

  if (argc == 1) {
    fprintf(stderr, "use: ./compiler [--lex|--parse|--codegen]\n");
    exit(1);
  }
  if (argc == 2) {
    // file is argv[1]
    // call compiler
    return run_compiler(argv[1], "");
  }
  if (argc == 3) {
    // file is argv[2]
    // find out which flag is being used
    if (strcmp(argv[1], "--lex") == 0 || strcmp(argv[1], "--parse") == 0 ||
        strcmp(argv[1], "--codegen") == 0) {
      return run_compiler(argv[2], argv[1]);
    }
    fprintf(stderr, "use: ./compiler [--lex|--parse|--codegen]\n");
    exit(1);
  }
  return 0;
}
