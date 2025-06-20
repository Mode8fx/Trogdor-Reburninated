#include "trogdor.h"

unsigned char trogdor_img[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 0x5c,
  0x02, 0x03, 0x00, 0x00, 0x00, 0xe6, 0x3e, 0x34, 0x6a, 0x00, 0x00, 0x00,
  0x0c, 0x50, 0x4c, 0x54, 0x45, 0xff, 0x00, 0xff, 0x62, 0xd4, 0x5f, 0x33,
  0x99, 0x33, 0xff, 0xcc, 0xcc, 0x30, 0x8b, 0x9c, 0x64, 0x00, 0x00, 0x05,
  0x0d, 0x49, 0x44, 0x41, 0x54, 0x48, 0xc7, 0xb5, 0x97, 0xbd, 0x6e, 0xdc,
  0x46, 0x10, 0xc7, 0x97, 0x3c, 0x5e, 0x90, 0xb0, 0x39, 0x9e, 0x40, 0x36,
  0xae, 0x12, 0x17, 0x81, 0xc1, 0x67, 0x30, 0x40, 0x2a, 0x38, 0x19, 0x86,
  0x2a, 0x2a, 0xb8, 0x53, 0xa1, 0x2a, 0x95, 0x8a, 0xcb, 0x4b, 0x5c, 0x00,
  0x05, 0x70, 0x17, 0xb8, 0x10, 0x10, 0x5d, 0x45, 0x23, 0xd2, 0x81, 0x5c,
  0x15, 0x7e, 0x04, 0x5d, 0xed, 0x37, 0x89, 0xab, 0x43, 0x4a, 0x83, 0xd0,
  0x66, 0x66, 0xe7, 0x63, 0x09, 0xc8, 0x70, 0xdc, 0x84, 0x85, 0x31, 0xde,
  0xf9, 0xcd, 0xc7, 0xee, 0x92, 0xf3, 0x3f, 0x19, 0xe3, 0x9f, 0xcc, 0x7c,
  0xd5, 0x33, 0xad, 0x6b, 0x31, 0xd5, 0x88, 0xd4, 0x9b, 0xa8, 0x15, 0xd5,
  0x0d, 0x5b, 0x85, 0xba, 0x97, 0xe2, 0x8e, 0x9a, 0x2c, 0x70, 0x2b, 0xc9,
  0x1c, 0x49, 0xc2, 0x7c, 0x2a, 0xde, 0x26, 0x57, 0xee, 0x78, 0xa9, 0xdc,
  0x52, 0x39, 0xa9, 0xd1, 0x14, 0x12, 0x1b, 0x9d, 0xc8, 0xda, 0x54, 0xbd,
  0xb9, 0x7a, 0x1b, 0x5f, 0xec, 0x39, 0x72, 0xea, 0x9d, 0xaa, 0x37, 0x97,
  0x56, 0xcc, 0xd9, 0x92, 0x39, 0x6b, 0xaf, 0xd1, 0x7a, 0x83, 0x7b, 0x43,
  0x2e, 0xfe, 0x1e, 0x8f, 0x0a, 0xb9, 0x6f, 0x37, 0xf0, 0x0f, 0x35, 0xf5,
  0xba, 0x4e, 0xad, 0xed, 0x88, 0x8b, 0xad, 0xc5, 0x35, 0xe0, 0x52, 0xdb,
  0x37, 0xc4, 0x95, 0xf6, 0x0e, 0x4b, 0x74, 0xe8, 0xb4, 0x16, 0x8b, 0xff,
  0x00, 0x6b, 0xb6, 0xc5, 0xa4, 0x57, 0x50, 0xc2, 0x62, 0xaa, 0xa3, 0x2c,
  0x26, 0xa7, 0xd9, 0x5a, 0xff, 0x6c, 0x4c, 0xdc, 0x42, 0x12, 0x9f, 0x39,
  0xc5, 0x24, 0x3e, 0xa2, 0xc4, 0x9e, 0x28, 0xc2, 0x2a, 0xb7, 0x26, 0xcb,
  0x98, 0xef, 0xc8, 0x80, 0x88, 0x1f, 0xc9, 0xc2, 0x1a, 0x25, 0x99, 0xef,
  0x0f, 0xb1, 0x15, 0x2e, 0x55, 0xae, 0x0c, 0x5c, 0xb2, 0x20, 0xce, 0x49,
  0xe6, 0x87, 0xbd, 0x44, 0x38, 0x89, 0xb8, 0x1f, 0xa0, 0xfb, 0x67, 0x10,
  0x88, 0xdc, 0x7e, 0x7e, 0x44, 0xdc, 0x60, 0x16, 0xa7, 0xc4, 0x1d, 0xa2,
  0xb9, 0xcf, 0x78, 0xef, 0xf6, 0xb8, 0x5b, 0x68, 0xfb, 0xe6, 0xbd, 0x3b,
  0x24, 0x6b, 0xdb, 0xc2, 0xff, 0x1e, 0x9c, 0x99, 0xc3, 0x1a, 0xa4, 0x72,
  0x83, 0x79, 0x05, 0x7d, 0x94, 0xc0, 0x1d, 0x80, 0x83, 0xdd, 0x94, 0x3b,
  0xe0, 0x52, 0xec, 0xcd, 0x5e, 0x3e, 0xb8, 0x7d, 0x09, 0x25, 0xe2, 0x7e,
  0xeb, 0xb0, 0x17, 0x38, 0x85, 0xdd, 0xaf, 0x10, 0xe1, 0x9f, 0xd2, 0xfe,
  0xe5, 0x86, 0x14, 0xcf, 0xc9, 0x6e, 0x91, 0x83, 0x2d, 0xc4, 0x76, 0x8d,
  0x1c, 0x6c, 0x21, 0xed, 0xef, 0x85, 0x83, 0xb0, 0x6a, 0x60, 0xeb, 0x0f,
  0x28, 0x82, 0x77, 0x62, 0x6d, 0x05, 0x6d, 0x19, 0xdc, 0x7e, 0x07, 0x11,
  0xbc, 0xb6, 0x99, 0x0c, 0x62, 0x11, 0x07, 0x5d, 0x4c, 0x88, 0x83, 0x2e,
  0x66, 0xc4, 0x95, 0xbb, 0x75, 0xf0, 0x9a, 0xd9, 0x81, 0xbd, 0xa6, 0xda,
  0x73, 0x31, 0xe3, 0x68, 0xa9, 0x97, 0x58, 0x7b, 0x03, 0xdc, 0xde, 0x27,
  0xbe, 0x04, 0xce, 0x87, 0xf6, 0x5b, 0x6a, 0x0a, 0x8f, 0xb5, 0x9b, 0x38,
  0x0a, 0xdd, 0x75, 0x9e, 0x83, 0xb5, 0x6d, 0xeb, 0x39, 0xa8, 0xc0, 0xc5,
  0x52, 0x7f, 0x33, 0x83, 0x58, 0xb3, 0x8a, 0x6f, 0x73, 0xf3, 0x72, 0xe0,
  0xfb, 0x37, 0xbe, 0x58, 0xc9, 0x6f, 0x0e, 0x7b, 0x2b, 0xa7, 0xde, 0x81,
  0x8b, 0x51, 0x03, 0x25, 0xbd, 0x38, 0xe4, 0x85, 0x35, 0xf6, 0x42, 0xf3,
  0x07, 0x2a, 0xb1, 0x91, 0x2c, 0xad, 0x51, 0xce, 0xf8, 0xed, 0xc6, 0xfe,
  0x6d, 0xc1, 0xed, 0xa6, 0x76, 0xe4, 0x95, 0x4f, 0x5e, 0x43, 0x63, 0xe9,
  0x04, 0x0f, 0x59, 0x3e, 0x27, 0xb4, 0x72, 0xf2, 0x76, 0x3c, 0x69, 0x52,
  0x4c, 0x52, 0x53, 0xb1, 0x8d, 0x4c, 0x10, 0x5c, 0x2b, 0x88, 0x03, 0xab,
  0x21, 0x0e, 0xbc, 0xcc, 0xc1, 0xb7, 0x3a, 0xe2, 0x5e, 0x78, 0x0e, 0xca,
  0x2e, 0x89, 0xc3, 0xb1, 0xe2, 0xb9, 0x0e, 0xa7, 0x14, 0x73, 0x59, 0x54,
  0x74, 0xca, 0xb5, 0xc2, 0xfd, 0xbc, 0x11, 0xee, 0x94, 0xf6, 0xdb, 0xe5,
  0xd3, 0x67, 0x2d, 0x71, 0x75, 0x72, 0x4e, 0x5c, 0x64, 0xe6, 0x17, 0xc4,
  0x25, 0xe6, 0x64, 0xcd, 0xe7, 0x72, 0x5d, 0xd0, 0xe6, 0x6d, 0xdb, 0xe4,
  0xeb, 0x8d, 0x8f, 0xf8, 0xad, 0x3e, 0xb3, 0xd4, 0xc1, 0x34, 0x7a, 0xd5,
  0xf1, 0xd6, 0xe5, 0x2c, 0x61, 0x1a, 0x9c, 0x5b, 0xe2, 0xfa, 0xb3, 0x0b,
  0xe6, 0xee, 0x4e, 0xd6, 0x9d, 0x1c, 0x16, 0x1f, 0x57, 0xa9, 0x16, 0x7f,
  0x97, 0xec, 0x6c, 0xf5, 0x5a, 0x5b, 0xcd, 0xdc, 0x69, 0x44, 0xab, 0x11,
  0xe1, 0xf4, 0xc3, 0x05, 0x6f, 0xb4, 0x86, 0x5c, 0x48, 0xb8, 0x91, 0x53,
  0xb1, 0x52, 0xbd, 0xaf, 0x52, 0xbd, 0xe1, 0x82, 0x23, 0x95, 0x85, 0xa8,
  0x94, 0xb5, 0x44, 0x4a, 0x98, 0x6f, 0x24, 0x74, 0xcc, 0xe9, 0xb4, 0x4f,
  0x82, 0x55, 0xab, 0x15, 0xb8, 0x24, 0x70, 0xaa, 0x00, 0x9a, 0x6e, 0x31,
  0xca, 0xd7, 0x68, 0x0d, 0x49, 0xa8, 0xa2, 0x00, 0x96, 0x72, 0x41, 0xc0,
  0x6a, 0x51, 0xa6, 0xa9, 0xd6, 0x35, 0x3a, 0xed, 0x57, 0x91, 0x2c, 0xea,
  0xd8, 0x1f, 0xf5, 0xf7, 0xc5, 0x27, 0x5a, 0x29, 0x97, 0x7d, 0x55, 0x80,
  0x49, 0x42, 0x07, 0x6a, 0x7c, 0x4e, 0x2c, 0x83, 0xe0, 0x65, 0x85, 0x06,
  0x88, 0xca, 0x8d, 0x4e, 0x60, 0xf9, 0x54, 0x18, 0x83, 0xce, 0x06, 0xfd,
  0x34, 0x2b, 0xe1, 0xa6, 0xca, 0x15, 0xca, 0x85, 0x13, 0x30, 0xc5, 0x89,
  0x66, 0xce, 0x35, 0x42, 0xb8, 0xe2, 0x38, 0x70, 0xc7, 0x86, 0xa5, 0x6f,
  0xa5, 0x75, 0x97, 0x5a, 0xf7, 0x2c, 0xec, 0xed, 0x02, 0xc7, 0xb6, 0xe7,
  0x70, 0x73, 0x28, 0x91, 0xd1, 0x12, 0xcf, 0xea, 0xb9, 0xcf, 0x8c, 0xdc,
  0x1b, 0x0f, 0xe2, 0xdb, 0x09, 0xd2, 0x07, 0x8b, 0xa0, 0x0c, 0x24, 0xa5,
  0x05, 0xbe, 0xb0, 0xc8, 0x99, 0x73, 0x7c, 0x25, 0x3d, 0xc7, 0xdf, 0x47,
  0xc7, 0x6f, 0xf1, 0x11, 0xa6, 0xf2, 0x6f, 0xf1, 0x6b, 0x4c, 0x85, 0x1f,
  0x05, 0x28, 0xa9, 0x51, 0x39, 0xfb, 0x53, 0xbe, 0x0f, 0x10, 0x4e, 0xfe,
  0x3e, 0x40, 0x38, 0xf9, 0xfb, 0x28, 0xcd, 0x67, 0x64, 0xef, 0x17, 0x51,
  0xd1, 0x7e, 0x63, 0x58, 0xeb, 0x76, 0x30, 0xe5, 0x3e, 0xaa, 0x28, 0x06,
  0x79, 0x0c, 0x6a, 0x2b, 0x2a, 0x3a, 0x71, 0x9e, 0xeb, 0x16, 0xb5, 0x71,
  0xe2, 0x9d, 0x3c, 0x8a, 0x77, 0xf6, 0x49, 0x8a, 0xcd, 0x80, 0x43, 0xc1,
  0x7c, 0x0b, 0x96, 0x5f, 0x7a, 0x37, 0x37, 0x15, 0x71, 0x57, 0x0b, 0xe3,
  0x88, 0x9b, 0x67, 0xa6, 0x72, 0x7f, 0x6f, 0xbd, 0xe2, 0x83, 0x65, 0xbd,
  0x60, 0x82, 0xf7, 0xd1, 0x0b, 0x66, 0x9f, 0x4d, 0x90, 0x83, 0x76, 0x6e,
  0x6b, 0xf0, 0x7e, 0x5c, 0xb7, 0x7e, 0x92, 0x39, 0x07, 0xb2, 0x84, 0x1f,
  0xee, 0xc4, 0x3d, 0xde, 0x58, 0xff, 0xe1, 0xce, 0xdc, 0xa7, 0xcb, 0x8e,
  0xe6, 0x80, 0x73, 0x32, 0xc7, 0x9d, 0xeb, 0xbd, 0xc6, 0x22, 0xb7, 0xf3,
  0xda, 0x89, 0xdc, 0xb6, 0xa3, 0xc1, 0xe8, 0x0e, 0xfc, 0xe9, 0x4f, 0xdc,
  0xc0, 0x53, 0x63, 0xe6, 0xfe, 0xe1, 0xb9, 0x50, 0xb9, 0x0f, 0x32, 0x17,
  0x9c, 0x0c, 0x0b, 0x50, 0x38, 0x1e, 0x11, 0x33, 0x27, 0x13, 0xa7, 0x1a,
  0x74, 0x92, 0x80, 0xb9, 0xc3, 0x06, 0x0d, 0x08, 0x2b, 0x67, 0x06, 0x05,
  0xe1, 0x88, 0x6a, 0xaf, 0x33, 0x0a, 0x82, 0x7b, 0x5a, 0x05, 0xee, 0xc6,
  0x2f, 0x4e, 0x80, 0xbb, 0xb4, 0xe2, 0xdc, 0x52, 0xe1, 0x09, 0xfd, 0x20,
  0xf1, 0x5c, 0xba, 0xf3, 0xd1, 0xc0, 0x95, 0x5b, 0xbf, 0x84, 0xbd, 0xac,
  0xb9, 0xc3, 0x81, 0xe4, 0x0f, 0x8a, 0xbc, 0x8c, 0x79, 0x4e, 0x0e, 0x87,
  0x94, 0xe7, 0x24, 0xfe, 0xa6, 0x18, 0xcf, 0x49, 0x5c, 0xac, 0x34, 0xb3,
  0x1b, 0x24, 0xa2, 0x32, 0x12, 0xc1, 0x6f, 0x56, 0x8b, 0xcd, 0x88, 0x3a,
  0x56, 0xc3, 0x48, 0x6c, 0xed, 0x68, 0xa0, 0xfa, 0xa3, 0xc6, 0x5f, 0x12,
  0xa4, 0xb1, 0x28, 0x99, 0xca, 0xc5, 0xca, 0xd5, 0xa4, 0x80, 0x1c, 0x1d,
  0x9a, 0xd1, 0x6a, 0xec, 0x6c, 0x48, 0x33, 0xfd, 0xb4, 0x48, 0xa9, 0x99,
  0x84, 0x94, 0xd2, 0xf8, 0xe1, 0xc3, 0x11, 0x38, 0x19, 0x4a, 0xe2, 0x6a,
  0xd2, 0x4c, 0x3f, 0x44, 0x53, 0xe2, 0x72, 0xd2, 0x4c, 0x78, 0xde, 0x29,
  0x87, 0x03, 0x89, 0xb8, 0x82, 0x55, 0xd1, 0xeb, 0x67, 0x4a, 0x5c, 0x7f,
  0x66, 0x32, 0xcf, 0xc5, 0xbf, 0x0b, 0x97, 0x2a, 0xf7, 0x22, 0x70, 0xe5,
  0xdb, 0xba, 0xf1, 0xde, 0xf8, 0x6e, 0x61, 0x6a, 0xe2, 0xae, 0xb3, 0x88,
  0xb8, 0x72, 0x59, 0x27, 0xc2, 0xa1, 0xe6, 0xf9, 0x6a, 0xf6, 0x24, 0xfa,
  0x89, 0x74, 0xb0, 0xcf, 0xa7, 0xe4, 0x4d, 0x6f, 0x9b, 0xbc, 0x7c, 0xa2,
  0x97, 0xa0, 0x8d, 0xac, 0x97, 0x20, 0xb5, 0xac, 0x97, 0x20, 0xa1, 0xff,
  0x93, 0x5e, 0x06, 0xf5, 0xfb, 0x0f, 0xbd, 0xb4, 0x57, 0x7a, 0xcf, 0x4f,
  0x54, 0x32, 0x88, 0x2e, 0xdc, 0x8d, 0x8c, 0xf7, 0xd8, 0x66, 0x72, 0xa9,
  0x5d, 0x2d, 0xb1, 0xb7, 0xe6, 0x09, 0x67, 0x32, 0xe1, 0xa2, 0xa0, 0x11,
  0x8b, 0xc0, 0xe9, 0x62, 0xc2, 0x1c, 0xa8, 0xa5, 0x72, 0xf9, 0x88, 0xe3,
  0x51, 0xae, 0x7f, 0x5a, 0x45, 0x23, 0xa5, 0x99, 0x8e, 0xb8, 0x46, 0xdc,
  0xcc, 0x25, 0x23, 0x1d, 0x5a, 0xaa, 0x15, 0xc4, 0x31, 0xfc, 0x69, 0xa5,
  0x1a, 0x3a, 0xea, 0xef, 0xcb, 0xcf, 0x0a, 0x23, 0xfe, 0x05, 0x9d, 0x16,
  0x27, 0xde, 0x13, 0xc3, 0x22, 0xba, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
  0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};
unsigned int trogdor_img_len = 1374;
