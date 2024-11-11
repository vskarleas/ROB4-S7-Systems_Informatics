// #############################################################################
// # File to_ppm_image_v2.c
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
    if (argc == 1)
    {
        fprintf(stderr, "Usage: %s ./ tga2ppm −−width −−height −−bpp −−in test.TGA −−out test.ppm\n", argv[0]);
        return 1;
    }

    char *input_file, *output_file;
    ui32_t flags = parse_args(argc, argv, &input_file, &output_file);

    // Read the binary image data
    FILE *f = fopen(input_file, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Error opening input file: %s\n", input_file);
        return 1;
    }

    img_t img;
    read_header(f, &img);
    ui32_t size = file_size(argv[1]);

    printf("File name: %s\n", input_file);
    printf("File size: %u\n", size);
    print_info(&img, flags);

    // Add pixels data to img_t
    read_pixels(f, &img);

    // Write the image to a PPM file
    write_ppm(output_file, &img);
    printf("PPM creation file was successful and image saved as: %s\n", output_file);

    fclose(f);        // closing the tga file

    return 0;
}