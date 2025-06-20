#include "game_over_text.h"

unsigned char game_over_text_img[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x9f, 0x00, 0x00, 0x01, 0x09,
  0x02, 0x03, 0x00, 0x00, 0x00, 0xf7, 0x3d, 0x1d, 0x99, 0x00, 0x00, 0x00,
  0x0c, 0x50, 0x4c, 0x54, 0x45, 0xff, 0x00, 0xff, 0xed, 0x1c, 0x24, 0x66,
  0x66, 0x66, 0xff, 0x00, 0x00, 0x51, 0x22, 0x3c, 0x28, 0x00, 0x00, 0x03,
  0x57, 0x49, 0x44, 0x41, 0x54, 0x68, 0xde, 0xed, 0xda, 0x3f, 0x6f, 0x9b,
  0x40, 0x14, 0x00, 0xf0, 0x67, 0x2c, 0x0f, 0xc0, 0xe0, 0x25, 0xee, 0x37,
  0x40, 0xb2, 0xbc, 0xf0, 0x05, 0xa2, 0x86, 0x8e, 0xdd, 0x32, 0x98, 0x28,
  0xca, 0x94, 0xb1, 0xf2, 0xa7, 0x60, 0xc9, 0x9c, 0xc5, 0x64, 0xa6, 0xaa,
  0x2c, 0xb9, 0xd7, 0x21, 0x5f, 0xc0, 0x0a, 0x48, 0x1d, 0xfb, 0x25, 0x32,
  0x56, 0x9e, 0x32, 0x46, 0x91, 0x55, 0xfa, 0xde, 0xbb, 0x8b, 0x31, 0x1c,
  0xd8, 0xe4, 0x8f, 0x9a, 0x26, 0xb9, 0x27, 0xd9, 0x70, 0xc7, 0x2f, 0x07,
  0x3c, 0x1f, 0xce, 0xd3, 0x25, 0xd0, 0x09, 0xc3, 0x90, 0x5e, 0x87, 0xd0,
  0x09, 0x00, 0x7a, 0xe1, 0x18, 0x30, 0x06, 0x61, 0xd0, 0xc3, 0xde, 0x4f,
  0xd8, 0x3f, 0x1e, 0xd0, 0x31, 0xd8, 0x03, 0x1b, 0x1b, 0x36, 0x43, 0x1b,
  0xa1, 0x27, 0x61, 0x1c, 0x06, 0x1e, 0xf6, 0x7e, 0x26, 0x18, 0x33, 0x9c,
  0x82, 0x23, 0x4e, 0xe6, 0xf6, 0xe4, 0x42, 0x48, 0x78, 0x22, 0xbe, 0xd2,
  0xb8, 0x13, 0x31, 0x18, 0x1d, 0x3b, 0x17, 0xce, 0x4c, 0x88, 0xe9, 0xf7,
  0x89, 0x38, 0x23, 0x08, 0x16, 0x91, 0x29, 0xbf, 0xcb, 0x7d, 0x1c, 0x37,
  0x80, 0x18, 0x77, 0xa7, 0xe0, 0xa1, 0xc0, 0x0e, 0xef, 0x1e, 0x3a, 0x30,
  0xb5, 0x22, 0x05, 0x1d, 0x3c, 0xf3, 0x09, 0x14, 0x30, 0xd9, 0x84, 0xbc,
  0x55, 0x10, 0x64, 0xcf, 0x1a, 0x82, 0x0e, 0x1d, 0xa8, 0x81, 0x7c, 0x2d,
  0xc7, 0x65, 0x08, 0x35, 0x90, 0x2f, 0xda, 0x3a, 0xdc, 0x0d, 0x29, 0x6b,
  0x2a, 0x3d, 0x65, 0x78, 0x46, 0x79, 0xd4, 0x60, 0xa4, 0x41, 0x99, 0x70,
  0x0d, 0x82, 0x0e, 0x47, 0x94, 0x70, 0x09, 0xcf, 0x3a, 0xa7, 0xe0, 0xd1,
  0xe7, 0x30, 0x99, 0xd5, 0xc0, 0x75, 0x92, 0x62, 0xf0, 0x28, 0x2f, 0x7c,
  0x33, 0x9e, 0x0e, 0x7b, 0x1a, 0x8c, 0x14, 0x4c, 0xca, 0xd0, 0xab, 0x42,
  0x3e, 0x85, 0xb7, 0x91, 0x92, 0x02, 0x7e, 0xa0, 0x7b, 0x0f, 0x3a, 0x5f,
  0x60, 0x78, 0xc4, 0xed, 0x3d, 0x3b, 0x18, 0xf2, 0x34, 0xab, 0x42, 0xda,
  0xf3, 0x02, 0x1a, 0x77, 0x0c, 0x6a, 0x52, 0xc8, 0x84, 0xe3, 0xbc, 0x0c,
  0xa1, 0x13, 0x1e, 0xaa, 0xec, 0x84, 0xa7, 0x74, 0xef, 0x03, 0x1c, 0x0d,
  0x61, 0x47, 0x4e, 0x5c, 0x2b, 0x24, 0x18, 0x13, 0xb4, 0x0b, 0x18, 0xf0,
  0xc4, 0x1d, 0x33, 0xb4, 0xe5, 0xc4, 0x7d, 0x20, 0x14, 0x47, 0x62, 0x8e,
  0xd3, 0x3c, 0x52, 0xf9, 0x16, 0xbc, 0x15, 0x94, 0x8d, 0x04, 0xbb, 0xc5,
  0xec, 0x54, 0xcc, 0xad, 0x98, 0xd2, 0x83, 0xed, 0x6d, 0xe1, 0xd1, 0x19,
  0x86, 0x45, 0xbb, 0x17, 0x6c, 0x83, 0x5b, 0xda, 0x4f, 0x87, 0xa3, 0xa6,
  0x6b, 0x6c, 0x3c, 0x60, 0xc2, 0x84, 0x09, 0x13, 0x4f, 0x89, 0x6e, 0x9e,
  0xe7, 0xf4, 0xba, 0x81, 0x6e, 0x06, 0xd0, 0xcf, 0x57, 0xd4, 0x79, 0x90,
  0x67, 0x7d, 0xec, 0xfd, 0x89, 0xfd, 0xab, 0x03, 0x3a, 0x06, 0xfb, 0xe0,
  0x62, 0xc3, 0x65, 0xe8, 0x22, 0xf4, 0x25, 0x4c, 0xf3, 0xcc, 0xc7, 0xde,
  0x5f, 0x04, 0x53, 0x86, 0x0b, 0xfc, 0xfa, 0xbd, 0x9b, 0xbb, 0xcb, 0x2b,
  0x21, 0xe1, 0x9d, 0xf8, 0x46, 0xe3, 0x2e, 0xc5, 0xc1, 0xe8, 0xd6, 0xb9,
  0x72, 0x2e, 0x85, 0x58, 0xfc, 0x58, 0x8a, 0x73, 0x82, 0x60, 0x11, 0x59,
  0xf0, 0xbb, 0xdc, 0xc7, 0x71, 0x33, 0x48, 0x71, 0x77, 0x01, 0x3e, 0x0a,
  0xec, 0xf0, 0xef, 0xa1, 0x03, 0x0b, 0x2b, 0x52, 0x90, 0x8a, 0x8f, 0x3b,
  0x28, 0x60, 0xb2, 0x09, 0x79, 0xab, 0x20, 0xc8, 0x9e, 0x35, 0x04, 0x1d,
  0x3a, 0x50, 0x03, 0xf9, 0x5a, 0x6e, 0xcb, 0x10, 0x6a, 0x20, 0x5f, 0xb4,
  0x75, 0xb3, 0x1b, 0x52, 0xd6, 0x54, 0x7a, 0xca, 0xf0, 0x9c, 0xf2, 0xa8,
  0xc1, 0x48, 0x83, 0x32, 0xe1, 0x1a, 0x04, 0x1d, 0x8e, 0x28, 0xe1, 0x12,
  0x9e, 0x77, 0xaf, 0xc1, 0xa7, 0xcf, 0x61, 0x79, 0x59, 0x03, 0xd7, 0x49,
  0x4a, 0xc1, 0xa7, 0xbc, 0xf0, 0xcd, 0xf8, 0x3a, 0xec, 0x6b, 0x30, 0x52,
  0x30, 0x29, 0x43, 0xbf, 0x0a, 0xf9, 0x14, 0xfe, 0x46, 0x4a, 0x0a, 0xf8,
  0x91, 0xee, 0x3d, 0xeb, 0xfe, 0x86, 0xe1, 0x1f, 0x6e, 0xef, 0xbb, 0xd9,
  0x90, 0xa7, 0x59, 0x15, 0xd2, 0x9e, 0x9f, 0xd1, 0xb8, 0x2b, 0x50, 0x93,
  0x42, 0x26, 0x1c, 0xe7, 0x65, 0x8e, 0xb3, 0xf7, 0x46, 0x65, 0x27, 0xbf,
  0xe6, 0x0d, 0x8e, 0x86, 0xb0, 0x2b, 0x27, 0xae, 0x95, 0x13, 0x4c, 0x09,
  0xba, 0x05, 0xcc, 0x40, 0xcd, 0x73, 0x84, 0xae, 0x9c, 0xb8, 0xcd, 0xd0,
  0x49, 0x6b, 0xa0, 0xf8, 0xb3, 0xb5, 0xf8, 0x10, 0x09, 0x16, 0x1f, 0x29,
  0x17, 0x1f, 0xab, 0xdd, 0x0f, 0x60, 0xca, 0xd9, 0xf9, 0xd7, 0xb0, 0x9f,
  0xb5, 0x84, 0x7e, 0x01, 0x93, 0x96, 0x70, 0x47, 0x30, 0x9c, 0xb7, 0x85,
  0xd5, 0x6b, 0x6e, 0x03, 0xfd, 0xb6, 0xd0, 0x94, 0x5c, 0x26, 0x4c, 0xbc,
  0x5c, 0x98, 0x95, 0x0f, 0xb3, 0xf2, 0x61, 0x56, 0x3e, 0x1a, 0x21, 0x3f,
  0x10, 0xda, 0xca, 0x87, 0xd0, 0x8b, 0x0f, 0x6f, 0x92, 0x94, 0x8a, 0x8f,
  0x39, 0xa7, 0xa7, 0x26, 0x1a, 0x17, 0x23, 0x9e, 0x0d, 0x0e, 0xda, 0xc2,
  0x98, 0xdf, 0xc7, 0x2d, 0xa1, 0x55, 0x03, 0x47, 0x51, 0x4b, 0x58, 0x8d,
  0x97, 0x81, 0xbc, 0xb4, 0xd4, 0x06, 0x72, 0x02, 0xb8, 0x40, 0x6a, 0xb3,
  0x78, 0xd5, 0x26, 0x5e, 0x03, 0xac, 0x96, 0x5c, 0xbd, 0xb6, 0x3f, 0xf8,
  0xe8, 0x33, 0x98, 0x78, 0xd7, 0x61, 0x8a, 0x0f, 0x53, 0x7c, 0x98, 0xe2,
  0xe3, 0x81, 0x7f, 0x76, 0x11, 0xbb, 0x57, 0x3e, 0x1a, 0x8b, 0x8f, 0xd7,
  0x10, 0xcf, 0xff, 0x5b, 0xe7, 0x4d, 0x43, 0x59, 0xed, 0xd5, 0xd5, 0x66,
  0x95, 0xf6, 0x9b, 0xaa, 0xcd, 0x1e, 0x08, 0x93, 0xdd, 0xb0, 0xcd, 0x72,
  0xd8, 0x7f, 0x54, 0x9b, 0x99, 0x78, 0x6a, 0x98, 0xe2, 0xc3, 0x14, 0x1f,
  0xa6, 0xf8, 0x78, 0x4c, 0xf1, 0x31, 0x0b, 0x54, 0xbe, 0x6b, 0xff, 0xe7,
  0x63, 0xa3, 0xf8, 0x70, 0xa2, 0x86, 0x67, 0xcf, 0x7c, 0x9b, 0x99, 0x78,
  0xcf, 0x51, 0x5f, 0xe3, 0xb6, 0x58, 0x89, 0xe3, 0xb0, 0x9e, 0x1f, 0x26,
  0x7a, 0x5f, 0xf5, 0x19, 0x6d, 0x5c, 0x56, 0xac, 0x46, 0x6c, 0xe0, 0xb6,
  0xa0, 0x42, 0xf3, 0x2f, 0xe1, 0xd7, 0x64, 0x81, 0xcb, 0x42, 0xb1, 0x77,
  0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};
unsigned int game_over_text_img_len = 936;
