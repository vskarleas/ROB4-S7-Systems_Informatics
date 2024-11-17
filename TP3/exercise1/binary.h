// #############################################################################
// # File binary.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>

#ifndef _BINARY_H_
#define _BINARY_H_

typedef unsigned char ui8_t; // char is 8 bits by default 

typedef unsigned short int ui16_t; // short int is 16 bits by default

typedef unsigned int ui32_t; // this is 32 bits by default

/* Read an unsigned 8-bit integer from a file */
ui8_t read_ui8(FILE *f);

/* Read an unsigned 16-bit integer from a file */
ui16_t read_ui16(FILE *f);

/* Read an unsigned 32-bit integer from a file */
ui32_t read_ui32(FILE *f);

/* Returns the size of a file in bytes */
ui32_t file_size(const char *fname);

#endif