// #############################################################################
// # File binary.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// ############################################################################# 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "binary.h"

/* Read an unsigned 8-bit integer from a file */
ui8_t read_ui8(FILE *f)
{
    ui8_t result;
    fread(&result, sizeof(result), 1, f);
    return result;
}

/* Read an unsigned 16-bit integer from a file */
ui16_t read_ui16(FILE *f)
{
    ui16_t result;
    fread(&result, sizeof(result), 1, f);
    return result;
}

/* Read an unsigned 32-bit integer from a file */
ui32_t read_ui32(FILE *f)
{
    ui32_t result;
    fread(&result, sizeof(result), 1, f);
    return result;
}

/* Returns the size of a file in bytes (octets) */
ui32_t file_size(FILE *fname)
{
    fseek(fname, 0, SEEK_END); // It is the file's pointer to the end of the file so that ftell can see the total size of the file
    long size = ftell(fname);

    ui32_t result;
    result = (unsigned int)size; // We need to cast the result to unsigned int because ftell returns a long int by default
    return result;
}
