#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Printing error message for allocating memory with corresponding general */
void allocation_error_print_general(char reference[512])
{
    fprintf(stderr, "Failed to allocate memory for %s.\n", reference);
    exit(-3);
}