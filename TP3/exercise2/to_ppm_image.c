// #############################################################################
// # File to_ppm_image.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "img.h"
#include "binary.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_tga_image> <output_ppm_image>\n", argv[0]);
        return 1;
    }

    // Read the binary image data
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        return 1;
    }

    //From print_data.c
    img_t img;
    read_header(f, &img);
    ui32_t size = file_size(f);

    printf("File name: %s\n", argv[1]);
    printf("File size: %u\n", size);
    printf("Image size: %u x %u\n", img.width, img.height);
    printf("Bits Per Pixel: %u\n", img.bitsperpixel);

    // Add pixels data to img_t
    read_pixels(f, &img);

    // Write the image to a PPM file
    write_ppm(argv[2], &img);
    printf("PPM creation file was succesful and image saved as: %s\n", argv[2]);

    fclose(f); //closing the tga file

}