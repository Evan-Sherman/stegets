#include "../lib/encode_decode.h"
#include "../lib/img/image_stego.h"
#include "string.h"
#include <iostream>

int main(int argc, char *argv[]) {
  const char *msg = "I am the super";

  const char *orig =
      "ENcode yourself into me pretty please my master oh please please please "
      "akdsgksfdkjsadfhlksahfdkjsadgfsalkdjfkajsdgflkdsajfdskflkjs";

  std::cout << "orig: " << orig << "\n";

  auto encoded = encode_LSB((unsigned char *)orig, strlen(orig), msg);
  std::cout << "encoded: " << encoded << "\n";

  auto dec = decode_LSB(encoded, strlen(orig));
  std::cout << "I got " << dec << "\n";

  bool did_encode =
      encode_img_LSB("rainbow.png", "encoded.png", "ENCODE ME PLEASE!");
  if (did_encode) {
    std::cout << "YAY!\n";
  } else {
    std::cout << "aww :(\n";
  }
  std::cout << "Decoded: " << (const char *)decode_img_LSB("encoded.png")
            << "\n";
}
