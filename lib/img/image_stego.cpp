#define cimg_use_jpeg
#define cimg_use_png

#include "image_stego.h"
#include "../../include/ANSI.h"
#include "../encode_decode.h"
#include "../helpers.h"
#include "CImg.h"
#include <cstring>
#include <stdio.h>

using namespace cimg_library;

// TODO: Implement proper handling of transparency. Remmber this only works for
// lossless formats
bool encode_img_LSB(std::string src, std::string dest, std::string msg) {
  CImg<unsigned char> image(src.c_str());

  int total_pixels = image.size();
  if (total_pixels < msg.length() * 8 + 8) {
    perror(YELLOW "UNABLE TO ENCODE MESSAGE, NOT ENOUGH PIXELS FOR GIVEN "
                  "MESSAGE\n" CRESET);
    return false;
  }

  auto bytes = image.data();
  auto enc_data = encode_LSB(bytes, total_pixels, msg.c_str());
  std::memcpy(image.data(), enc_data, total_pixels);
  image.save(dest.c_str());

  return true;
}

unsigned char *decode_img_LSB(std::string src) {

  CImg<unsigned char> image(src.c_str());
  auto decoded = decode_LSB(image.data(), image.size());
  return decoded;
}
