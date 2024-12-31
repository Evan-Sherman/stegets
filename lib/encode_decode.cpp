#include "encode_decode.h"
#include "../include/ANSI.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char encode_bit_LSB(unsigned char byte, bool bit) {
  ByteBits bb;
  bb.all = byte;
  bb.bits.bit0 = bit;
  return bb.all;
}

bool decode_bit_LSB(unsigned char byte) {
  ByteBits bb;
  bb.all = byte;
  return bb.bits.bit0;
}

unsigned char *encode_LSB(unsigned char *bytes, int len, const char *msg) {
  unsigned char *encoded =
      (unsigned char *)malloc(sizeof(unsigned char) * len + 1);
  ByteBits curr_msg_byte;
  unsigned int msg_len = strlen(msg);
  unsigned int curr_index = 0;

  // if lenth of message + null character doesn't fit
  if (msg_len * 8 + 8 >= len) {
    perror(YELLOW "MESSAGE IS TOO LARGE, CANNOT ENCODE\n" CRESET);
    free(encoded);
    return NULL;
  }
  for (; curr_index <= msg_len; curr_index++) { // <= so that we get \0 encoded

    curr_msg_byte.all = msg[curr_index];
    encoded[curr_index * 8] =
        encode_bit_LSB(bytes[curr_index * 8], curr_msg_byte.bits.bit0);
    encoded[(curr_index * 8) + 1] =
        encode_bit_LSB(bytes[(curr_index * 8) + 1], curr_msg_byte.bits.bit1);
    encoded[(curr_index * 8) + 2] =
        encode_bit_LSB(bytes[(curr_index * 8) + 2], curr_msg_byte.bits.bit2);
    encoded[(curr_index * 8) + 3] =
        encode_bit_LSB(bytes[(curr_index * 8) + 3], curr_msg_byte.bits.bit3);
    encoded[(curr_index * 8) + 4] =
        encode_bit_LSB(bytes[(curr_index * 8) + 4], curr_msg_byte.bits.bit4);
    encoded[(curr_index * 8) + 5] =
        encode_bit_LSB(bytes[(curr_index * 8) + 5], curr_msg_byte.bits.bit5);
    encoded[(curr_index * 8) + 6] =
        encode_bit_LSB(bytes[(curr_index * 8 + 6)], curr_msg_byte.bits.bit6);
    encoded[(curr_index * 8) + 7] =
        encode_bit_LSB(bytes[(curr_index * 8 + 7)], curr_msg_byte.bits.bit7);
  }
  for (int i = curr_index * 8; i < len; i++) {
    encoded[i] = bytes[i];
  }
  encoded[len] = '\0';
  return encoded;
}

unsigned char *decode_LSB(unsigned char *bytes, int len) {
  unsigned char *decoded =
      (unsigned char *)malloc(sizeof(char) * (len / 8) + 1);
  ByteBits bb;
  for (int i = 0; i < len / 8; i++) {
    if ((i * 8) + 7 >= len) {
      decoded[i] = '\0';
      break;
    }
    bb.bits.bit0 = decode_bit_LSB(bytes[(i * 8)]);
    bb.bits.bit1 = decode_bit_LSB(bytes[(i * 8) + 1]);
    bb.bits.bit2 = decode_bit_LSB(bytes[(i * 8) + 2]);
    bb.bits.bit3 = decode_bit_LSB(bytes[(i * 8) + 3]);
    bb.bits.bit4 = decode_bit_LSB(bytes[(i * 8) + 4]);
    bb.bits.bit5 = decode_bit_LSB(bytes[(i * 8) + 5]);
    bb.bits.bit6 = decode_bit_LSB(bytes[(i * 8) + 6]);
    bb.bits.bit7 = decode_bit_LSB(bytes[(i * 8) + 7]);

    decoded[i] = bb.all;
    if (decoded[i] == '\0') {
      break;
    }
  }
  return decoded;
}
