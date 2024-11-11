// #############################################################################
// # File print_data.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "img.h"
#include "binary.h"

int main(int argc, char *argv[])
{
    if (argc != 2) // We expect one argument that is the TGA image
    {
        fprintf(stderr, "Usage: %s <image.tga>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) //error handling in the case that the file is NULL
    {
        perror("Error opening the image file");
        return 1;
    }

    img_t img;
    read_header(f, &img);
    ui32_t size = file_size(argv[1]);

    printf("File name: %s\n", argv[1]);
    printf("File size: %u bytes\n", size);
    printf("Image size: %u x %u\n", img.width, img.height);
    printf("Bits Per Pixel: %u\n", img.bitsperpixel);

    fclose(f); //importsnt to close the file to prevent memory leaks
    return 0;
}