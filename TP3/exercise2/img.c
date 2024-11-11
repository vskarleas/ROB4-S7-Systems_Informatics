// #############################################################################
// # File img.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WIDTH 1 // in 32 bits is 0...00001
#define HEIGHT 2 // in 32 bits is 0...00010
#define BPP 4 // in 32 bits is 0...00100

#include "img.h"
#include "binary.h"

/* Thi sis a function taht reads the header of a TGA image */
void read_header(FILE *f, img_t *img)
{
    // INFO: The file has already been opened in the main function. Here we only perfom the read
    // Reading the header of the image
    img->idlength = read_ui8(f);
    img->colourmaptype = read_ui8(f);
    img->datatypecode = read_ui8(f);
    img->colourmaporigin = read_ui16(f);
    img->colourmaplength = read_ui16(f);
    img->colourmapdepth = read_ui8(f);
    img->x_origin = read_ui16(f);
    img->y_origin = read_ui16(f);
    img->width = read_ui16(f);
    img->height = read_ui16(f);
    img->bitsperpixel = read_ui8(f);
    img->imagedescriptor = read_ui8(f);
}

ui32_t *get_pixel(const img_t *img, int row, int col)
{
    // INFO: The pixel data is stored in a 1D array. We need to calculate the index of the pixel in the array
    int index = row * img->width + col;
    return &img->pixels[index];
}

/* We need to pack the RGB values into a single 32-bit integer */
ui32_t make_pixel(ui8_t r, ui8_t g, ui8_t b)
{
    // INFO: We have 8 bit sleft for the transparency that are not declared here
    //  since the syntax of every pixel is [r, g, b, transparency]
    ui32_t result = (r << 24) | (g << 16) | (b << 8); // Using bits shifting to place the values in the correct positions. HERE WE ARE READING FROM LEFT TO RIGHT
    return result;
}

/* Function to read the pixel data of a TGA image and save it to the img_t structure */
void read_pixels(FILE *f, img_t *img)
{
    // Allocating the right amount of memory for the pixels
    img->pixels = (ui32_t *)malloc(img->width * img->height * sizeof(ui32_t)); // casting to ui32_t since this is the declaration at img.h for pour pixels table
    if (img->pixels == NULL)
    {
        perror("Error allocating memory for the pixel data");
        exit(1);
    }

    // Seeking to the beginning of the pixel data
    int offset = (unsigned short int)(img->idlength) + (unsigned short int)(img->colourmaptype) * (img->colourmaplength);

    fseek(f, offset, SEEK_SET); // fseek moves the file pointer to the specified position that we are calculating by using the formula given in the subject

    // Found out that on TGA the pixels are declared from bottom to top and from left to right. That is why read the pixels as follows
    for (int i = img->height - 1; i >= 0; i--) // i represnts the rows
    {
        for (int j = 0; j < img->width; j++) // j is columns of the image
        {
            ui8_t r, g, b;

            // All the colors are stored like "b, g, r". So we make sure that we read in order
            fread(&b, sizeof(ui8_t), 1, f);
            fread(&g, sizeof(ui8_t), 1, f);
            fread(&r, sizeof(ui8_t), 1, f);

            ui32_t pixel = make_pixel(r, g, b);
            img->pixels[i * img->width + j] = pixel; // Storing the pixel data in the array of pixels
        }
    }
}

/* Function to write the pixel data of a TGA image to a PPM file */
void write_ppm(const char *filename, const img_t *img)
{
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        perror("Error opening the PPM file");
        exit(1);
    }

    // Writing the header of the PPM file
    fprintf(f, "P6\n");
    fprintf(f, "%u %u\n", img->width, img->height);
    fprintf(f, "255\n");

    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            // Getting the pixel data from the image
            ui32_t *pixel_pointer = get_pixel(img, i, j);
            ui32_t pixel = *pixel_pointer;

            // Extracting the RGB values from the pixel data
            ui8_t r = (pixel >> 24);
            ui8_t g = (pixel >> 16);
            ui8_t b = (pixel >> 8);

            // Writing the pixel data
            fwrite(&r, sizeof(ui8_t), 1, f);
            fwrite(&g, sizeof(ui8_t), 1, f);
            fwrite(&b, sizeof(ui8_t), 1, f);
        }
    }

    fclose(f); // clsoing the ppm file
}

/* Function to print the information about the image */
void print_info(const img_t *img, ui32_t data)
{
    //when bitwise returns 0, then if(0) <=> false
    // != 0 if and only if the last bit is 1
    /* ex: data == 0101 meaning that bpp and width are applied. Then when we test for & 0001 and & 0100 the operation will return 1 meaming that it will proceed */
    if (data & WIDTH) 
    {
        printf("Width: %u\n", img->width);
    }
    if (data & HEIGHT)
    {
        printf("Height: %u\n", img->height);
    }
    if (data & BPP)
    {
        printf("Bits per pixel: %u\n", img->bitsperpixel);
    }
}

ui32_t parse_args(int argc, char **argv, char **input, char **output)
{
    ui32_t flags = 0;
    *input = NULL;
    *output = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--width") == 0)
        {
            flags = flags | WIDTH;
        }
        else if (strcmp(argv[i], "--height") == 0)
        {
            flags = flags | HEIGHT;
        }
        else if (strcmp(argv[i], "--bpp") == 0)
        {
            flags = flags | BPP;
        }
        else if (strcmp(argv[i], "--in") == 0 && i + 1 < argc) // make sure that there is still another argument after it
        {
            *input = argv[++i];
        }
        else if (strcmp(argv[i], "--out") == 0 && i + 1 < argc)
        {
            *output = argv[++i];
        }
    }

    if (*input == NULL || *output == NULL)
    {
        fprintf(stderr, "Input and output files must be specified\n");
        exit(1);
    }

    return flags;
}