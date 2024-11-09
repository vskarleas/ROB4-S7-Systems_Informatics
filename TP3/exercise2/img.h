// #############################################################################
// # File img.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#ifndef _IMG_H_
#define _IMG_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary.h"

/* TGA images format header declaration */
typedef struct
{
    ui8_t  idlength;
    ui8_t  colourmaptype;
    ui8_t  datatypecode;
    ui16_t colourmaporigin;
    ui16_t colourmaplength;
    ui8_t  colourmapdepth;
    ui16_t x_origin;
    ui16_t y_origin;
    ui16_t width; // on the subject says ui16_t but I would prefer to put ui32_t
    ui16_t height;
    ui8_t  bitsperpixel;
    ui8_t  imagedescriptor;

    ui32_t *pixels; // pointer to the pixel data
} img_t;

/* This is a function that reads the header of a TGA image */
void read_header(FILE *f, img_t *img);

/* This is a function that returns a pointer to a pixel in the image */
ui32_t *get_pixel(const img_t *img, int row, int col);

/* We need to pack the RGB values into a single 32-bit integer */
ui32_t make_pixel(ui8_t r, ui8_t g, ui8_t b);

/* This is a function that reads the pixel data of a TGA image and saves it to the  */
void read_pixels(FILE *f, img_t *img);

/* This is a function that writes the pixel data of a TGA image to a PPM file */
void write_ppm(const char *filename, const img_t *img);

/* This is a function that prints the information of a TGA image according to the options */
void print_info(const img_t *img, ui32_t data);

/* This is a function that parses the arguments of the program */
ui32_t parse_args(int argc, char **argv, char **input, char **output);

#endif