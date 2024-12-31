#include <string>
#ifndef _IMG_HANDLER_H_
#define _IMG_HANDLER_H_

bool encode_img_LSB(std::string src, std::string dest, std::string msg);
unsigned char *decode_img_LSB(std::string src);
#endif
