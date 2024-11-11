// #############################################################################
// # File binary.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef _BINARY_H_
#define _BINARY_H_

typedef unsigned char ui8_t; // char is 8 bits by default 

typedef unsigned short int ui16_t; // short int is 16 bits by default

typedef unsigned int ui32_t; // this is 32 bits by default

ui8_t read_ui8(FILE *f);

ui16_t read_ui16(FILE *f);

ui32_t read_ui32(FILE *f);

/* Returns the file's size */
ui32_t file_size(const char *fname);

#endif