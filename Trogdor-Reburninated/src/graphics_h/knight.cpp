#include "knight.h"

unsigned char knight_img[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x30,
  0x02, 0x03, 0x00, 0x00, 0x00, 0xaa, 0x1f, 0x26, 0x07, 0x00, 0x00, 0x00,
  0x09, 0x50, 0x4c, 0x54, 0x45, 0xff, 0x00, 0xff, 0x90, 0x90, 0x90, 0x2a,
  0x5b, 0xc6, 0x37, 0xa8, 0x5f, 0x60, 0x00, 0x00, 0x01, 0xcc, 0x49, 0x44,
  0x41, 0x54, 0x38, 0xcb, 0xbd, 0x94, 0xb1, 0x4e, 0xc3, 0x30, 0x10, 0x86,
  0xcf, 0x28, 0x41, 0x22, 0x93, 0x8b, 0xc8, 0xc2, 0xce, 0x40, 0x9f, 0xc2,
  0xac, 0x4c, 0x19, 0xe2, 0x0a, 0x75, 0x62, 0x44, 0x7d, 0x8a, 0x30, 0xb0,
  0x33, 0xd0, 0xbd, 0x48, 0x54, 0x4a, 0xee, 0x29, 0xf9, 0x7f, 0x3b, 0xb6,
  0x53, 0x84, 0x54, 0x26, 0x86, 0x5a, 0x97, 0x2f, 0x5f, 0xef, 0x2e, 0xf1,
  0x39, 0x22, 0x22, 0x15, 0x7e, 0x62, 0x1c, 0xd7, 0xb0, 0xdc, 0xc8, 0x29,
  0x94, 0x55, 0x01, 0x36, 0x5b, 0x05, 0x8a, 0x04, 0x5a, 0x07, 0x21, 0x5c,
  0x77, 0xa7, 0xd0, 0x32, 0x65, 0x45, 0xd9, 0x94, 0x3a, 0x76, 0x51, 0xc7,
  0x52, 0x4e, 0x82, 0x64, 0xc1, 0x16, 0xa1, 0x19, 0x11, 0x5d, 0x28, 0x05,
  0x1d, 0x00, 0xd6, 0x87, 0x19, 0x0a, 0x21, 0xe2, 0xf6, 0x05, 0x42, 0xbd,
  0x85, 0x60, 0x36, 0x14, 0xfc, 0x61, 0x86, 0x42, 0xc8, 0xf8, 0x89, 0xc2,
  0x86, 0x82, 0x0f, 0xc2, 0xf3, 0x0c, 0x85, 0xf0, 0x2f, 0x25, 0x94, 0x42,
  0xa3, 0x07, 0x31, 0x8d, 0x0e, 0x68, 0x53, 0x35, 0x42, 0x2b, 0x84, 0x8c,
  0xf1, 0xbf, 0x6a, 0xad, 0xbe, 0x83, 0x30, 0x8a, 0xbb, 0xd0, 0xa3, 0x0f,
  0xb0, 0x12, 0x42, 0x0a, 0x93, 0x77, 0x49, 0xd8, 0xf7, 0x76, 0x16, 0x26,
  0xff, 0xf0, 0xbb, 0x50, 0x65, 0xc1, 0xb9, 0x28, 0xf4, 0x8c, 0x5b, 0xc6,
  0xf5, 0x23, 0x04, 0x73, 0x4d, 0x21, 0xc0, 0x55, 0x14, 0xd6, 0x8c, 0x1b,
  0xd5, 0x3d, 0xaa, 0x43, 0x90, 0x9d, 0x4e, 0x7d, 0x84, 0x97, 0x84, 0x14,
  0xd4, 0x4b, 0x12, 0x8e, 0x9d, 0xd1, 0x28, 0x00, 0xde, 0x46, 0x41, 0xbc,
  0xf7, 0x22, 0x2d, 0x97, 0xda, 0x23, 0xa5, 0xe1, 0xb2, 0x80, 0x7c, 0xee,
  0x0f, 0xe6, 0xc1, 0x23, 0x37, 0x3a, 0x39, 0xbc, 0x1d, 0x3d, 0x81, 0x8c,
  0x87, 0x2c, 0x8c, 0x92, 0x85, 0xe1, 0x3f, 0x05, 0x59, 0x0f, 0x71, 0x0b,
  0x71, 0x73, 0x4c, 0x5b, 0xb8, 0x80, 0x67, 0x85, 0x2a, 0x8f, 0x6f, 0x9c,
  0xf7, 0xee, 0x07, 0x8c, 0x07, 0x20, 0xdc, 0x33, 0x65, 0x50, 0x0b, 0x9c,
  0xcf, 0x42, 0x9c, 0x77, 0x9b, 0xcf, 0xd5, 0x02, 0x22, 0x91, 0x09, 0xb2,
  0x63, 0x76, 0x9b, 0xb3, 0x9b, 0x45, 0x86, 0x2c, 0xd8, 0x2c, 0x98, 0x85,
  0xd0, 0x8c, 0x26, 0xb4, 0x8e, 0x2b, 0x1d, 0xec, 0xdc, 0x7a, 0x82, 0x41,
  0xf0, 0x8c, 0xf7, 0x0e, 0xc2, 0xb1, 0x83, 0x70, 0xdf, 0x2f, 0x20, 0x85,
  0xab, 0x10, 0x7b, 0x0a, 0x7b, 0x0a, 0x77, 0xfd, 0x02, 0xfe, 0xad, 0x84,
  0xbe, 0xf2, 0xad, 0x0f, 0x14, 0x46, 0x0b, 0x3a, 0xa2, 0xc1, 0x04, 0xd9,
  0xb5, 0x22, 0x6e, 0x37, 0x7a, 0x70, 0xdc, 0x2b, 0x6b, 0xfc, 0x4e, 0xf1,
  0x20, 0x09, 0x22, 0xaf, 0xdf, 0x26, 0xa1, 0xf6, 0x49, 0xb0, 0x19, 0xa2,
  0xd0, 0x6f, 0x82, 0xcb, 0xb0, 0x0a, 0xc2, 0x9b, 0x43, 0xfc, 0xd9, 0x51,
  0xe8, 0x29, 0xac, 0x0a, 0xb4, 0x41, 0x50, 0x7c, 0x08, 0x30, 0x20, 0x10,
  0x50, 0x14, 0xcb, 0x57, 0x81, 0xe8, 0xbc, 0xdd, 0x25, 0xc1, 0x6c, 0x66,
  0x61, 0x2a, 0xf0, 0x3d, 0xcc, 0xbe, 0x8b, 0x67, 0x01, 0x4b, 0x3f, 0x9f,
  0x85, 0x02, 0xb1, 0x6f, 0x65, 0xfa, 0xb6, 0x79, 0x24, 0xeb, 0x7f, 0x9e,
  0xfa, 0xf3, 0x42, 0x9c, 0x72, 0x0a, 0x71, 0xf4, 0xf5, 0x04, 0x9e, 0x15,
  0xbe, 0x01, 0x22, 0x42, 0x3b, 0x90, 0x8b, 0x72, 0x20, 0xd6, 0x00, 0x00,
  0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};
unsigned int knight_img_len = 538;
