#include "helpers.h"
#include "../include/ANSI.h"
#include <stdio.h>
#include <stdlib.h>

void print_byte_bits(ByteBits bb) {
  printf("Char: \"%c\" Bits: %d%d%d%d%d%d%d%d\n", bb.all, bb.bits.bit7,
         bb.bits.bit6, bb.bits.bit5, bb.bits.bit4, bb.bits.bit3, bb.bits.bit2,
         bb.bits.bit1, bb.bits.bit0);
}

void print_pair(Pair pair) { printf("(%ld, %ld)\n", pair.val1, pair.val2); }

struct BufWithSize *read_all_bytes(const char *file_name) {

  unsigned char *buf;
  unsigned long int file_size;
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    fprintf(stderr, YELLOW "Error acessing/finding file %s\n" CRESET,
            file_name);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  rewind(file);

  buf = (unsigned char *)malloc(file_size + 1);
  if (buf == NULL) {
    perror(YELLOW "Memory allocation error\n" CRESET);
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buf, 1, file_size, file);
  if (bytes_read != file_size) {
    fprintf(stderr, "Error reading file %s" CRESET, file_name);
    fclose(file);
    free(buf);
    return NULL;
  }
  fclose(file);
  BufWithSize *ret = (BufWithSize *)malloc(sizeof(struct BufWithSize));
  ret->bytes = buf;
  ret->size = bytes_read;
  return ret;
}
