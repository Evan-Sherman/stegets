#include <stdbool.h>
#include <stdint.h>

#ifndef _HELP_STRUCTS_
#define _HELP_STRUCTS_
typedef union ByteBits {
  struct { // In Big Endian, bit0 (LSB) is left most
    unsigned bit0 : 1;
    unsigned bit1 : 1;
    unsigned bit2 : 1;
    unsigned bit3 : 1;
    unsigned bit4 : 1;
    unsigned bit5 : 1;
    unsigned bit6 : 1;
    unsigned bit7 : 1;
  } bits;

  unsigned char all;
} ByteBits;

typedef struct Pair {
  long int val1;
  long int val2;
} Pair;

typedef struct BufWithSize {
  unsigned char *bytes;
  unsigned long int size;
} BufWithSize;
#endif

struct BufWithSize *read_all_bytes(const char *);
void print_pair(Pair);
void print_byte_bits(ByteBits);
