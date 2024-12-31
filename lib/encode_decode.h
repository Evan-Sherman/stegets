
#include <stdbool.h>
#ifndef _ENCODE_FLAG_
#define _ENCODE_FLAG_
typedef enum EncodeFlag { LSB, BPCS } EncodeFlag;
#endif
unsigned char *encode_LSB(unsigned char *bytes, int len, const char *msg);
unsigned char *decode_LSB(unsigned char *bytes, int len);
unsigned char encode_bit_LSB(unsigned char, bool);
bool decode_bit_LSB(unsigned char);
