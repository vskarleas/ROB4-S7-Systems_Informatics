// #############################################################################
// # File test1.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// ############################################################################# 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "binary.h"

/* Testing the functions read_ui8, read_ui16 and read_ui32. Check out the create_test_binary.c 
to check out the original content of the test_binary.bin file */
int main(int argc, char **argv)
{
    FILE *file = fopen("test_binary.bin", "rb");
    if (file == NULL)
    {
        perror("Error opening the binary file");
        return 1;
    }

    // Read 8-bit integers
    for (int i = 0; i < 5; i++) //Because we have 5 8-bit integers
    {
        ui8_t ui8 = read_ui8(file);
        printf("Read No %d (8-bit integer): %u\n",i+1, ui8); //INFO: %u is used to print unsigned integers
    }

    printf("======================\n");

    // Read 16-bit integers
    for (int i = 0; i < 5; i++)
    {
        ui16_t ui16 = read_ui16(file);
        printf("Read No %d (16-bit integer): %u\n",i+1, ui16);
    }

    printf("======================\n");

    // Read 32-bit integers
    for (int i = 0; i < 5; i++)
    {
        ui32_t ui32 = read_ui32(file);
        printf("Read No %d (32-bit integer): %u\n",i+1, ui32);
    }

    fclose(file);
    return 0;
}