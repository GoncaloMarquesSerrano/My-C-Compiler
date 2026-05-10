#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdint.h>

unsigned char *read_file(const char *file_name, uint64_t *file_size);

#endif // FILE_READER_H
