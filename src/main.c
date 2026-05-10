#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void build_filenames(const char *input, char *preprocessed, char *assembly,
                     char *executable, size_t buf_size) {
  char *pos = strrchr(input, '.');

  if (pos == NULL) {
    fprintf(stderr, "No extension found");
    exit(1);
  }

  size_t len = pos - input;

  char filename[buf_size];

  strncpy(filename, input, len);
  filename[len] = '\0';

  snprintf(preprocessed, buf_size, "%s.i", filename);
  snprintf(assembly, buf_size, "%s.s", filename);
  snprintf(executable, buf_size, "%s", filename);
}

int run_compiler(const char *input_file, const char *flag) { return 0; }

int main(int argc, char *argv[]) {

  char preprocessed[512];
  char assembly[512];
  char executable[512];

  if (argc == 1) {
    fprintf(stderr, "use: ./compiler [--lex|--parse|--codegen]");
    exit(1);
  }
  if (argc == 2) {
    // file is argv[1]
    // call compiler
    build_filenames(argv[1], preprocessed, assembly, executable,
                    sizeof(preprocessed));
    run_compiler(argv[1], "");
  }
  if (argc == 3) {
    // file is argv[2]
    build_filenames(argv[2], preprocessed, assembly, executable,
                    sizeof(preprocessed));

    // find out which flag is being used
    if (strcmp(argv[1], "--lex") == 0) {
      run_compiler(argv[2], "--lex");
      return 0;
    } else if (strcmp(argv[1], "--parse") == 0) {
      run_compiler(argv[2], "--parse");
      return 0;
    } else if (strcmp(argv[1], "--codegen") == 0) {
      run_compiler(argv[2], "--codegen");
      return 0;
    } else {
      fprintf(stderr, "use: ./compiler [--lex|--parse|--codegen]");
      exit(1);
    };
  }

  return 0;
}
