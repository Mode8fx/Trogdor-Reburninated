#include "archer.h"

unsigned char archer_img[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x28,
  0x02, 0x03, 0x00, 0x00, 0x00, 0xf1, 0x90, 0x50, 0xfe, 0x00, 0x00, 0x00,
  0x0c, 0x50, 0x4c, 0x54, 0x45, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x99, 0x00, 0xe1, 0xaf, 0x68, 0x93, 0x73, 0x2d, 0xf0, 0x00, 0x00, 0x00,
  0xe5, 0x49, 0x44, 0x41, 0x54, 0x18, 0xd3, 0x3d, 0x90, 0x41, 0x6a, 0xc3,
  0x30, 0x10, 0x45, 0x7f, 0x6c, 0x43, 0x40, 0x18, 0x22, 0xc8, 0x25, 0x82,
  0x56, 0x5e, 0x77, 0x65, 0xe8, 0x6d, 0xda, 0x4b, 0xf8, 0x28, 0x5e, 0xaa,
  0xd3, 0x42, 0xaf, 0xe0, 0x40, 0x0e, 0x90, 0x6b, 0xb4, 0xab, 0xac, 0xbb,
  0x71, 0xdf, 0x8c, 0x83, 0xb5, 0x78, 0x3c, 0xd0, 0x47, 0xf3, 0x47, 0xea,
  0xc4, 0x09, 0xe8, 0x20, 0xa5, 0x0d, 0xce, 0xa2, 0xc3, 0x02, 0x74, 0x94,
  0x6c, 0xea, 0x06, 0xa0, 0xb3, 0x9a, 0x6f, 0xe5, 0x1e, 0xa0, 0x5a, 0x95,
  0x5b, 0xa0, 0x57, 0xd7, 0x51, 0xcb, 0xa6, 0x27, 0x74, 0x38, 0x49, 0xef,
  0x66, 0x36, 0xbf, 0x39, 0x42, 0xab, 0x6b, 0x25, 0x90, 0xcc, 0x46, 0xbd,
  0x98, 0xa1, 0x8d, 0xeb, 0x2f, 0x7a, 0x76, 0xcd, 0x6d, 0x0a, 0x85, 0x8c,
  0x40, 0x8f, 0x2a, 0xc5, 0x18, 0x5c, 0x8c, 0x3a, 0x97, 0x64, 0xd4, 0x49,
  0xae, 0x84, 0x03, 0xd1, 0xda, 0x02, 0x51, 0xbf, 0xec, 0x50, 0xb3, 0x43,
  0xf9, 0x89, 0x59, 0x14, 0x0b, 0xa8, 0x3a, 0xab, 0xda, 0xd1, 0x1f, 0xd1,
  0x1d, 0xf4, 0x04, 0xfe, 0x26, 0xdd, 0xc0, 0xd0, 0xf9, 0x3a, 0xe8, 0xaa,
  0x65, 0xd3, 0xab, 0xd6, 0xd6, 0xc7, 0x3e, 0x5c, 0x1f, 0x3d, 0x4a, 0x45,
  0xfb, 0x71, 0x7c, 0x50, 0x0e, 0x2d, 0xa1, 0xbe, 0xea, 0xd5, 0xec, 0x8b,
  0x80, 0xf1, 0x59, 0xe8, 0xe7, 0x53, 0x6f, 0x5c, 0xf1, 0x98, 0x07, 0x50,
  0x1f, 0x61, 0xb5, 0xea, 0xce, 0x7f, 0x30, 0xd8, 0xe6, 0x8b, 0x46, 0x6e,
  0xa8, 0x43, 0x14, 0x75, 0xc4, 0x4a, 0x39, 0xe0, 0x75, 0xb5, 0x41, 0xd3,
  0x8e, 0x7f, 0x01, 0x23, 0x6c, 0x35, 0x4f, 0x7d, 0x47, 0x6c, 0x00, 0x00,
  0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};
unsigned int archer_img_len = 310;
