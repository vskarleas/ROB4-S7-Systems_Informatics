// #############################################################################
// # File test2.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// ############################################################################# 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "binary.h"

/* Testing teh file_size function */
int main(int argc, char **argv)
{
    FILE *file = fopen("test_binary.bin", "rb");
    if (file == NULL)
    {
        perror("Error opening the binary file");
        return 1;
    }

    ui32_t size = file_size(file);
    printf("The size of the file is: %u bytes\n", size);

    fclose(file);
    return 0;

}