// #############################################################################
// # File memory.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// ############################################################################# 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "memory.h"

/* Freeing a 2D array */
void free_2d(int **table, int n) // n = rows = lignes
{
    for (int i = 0; i < n; i++)
        free(table[i]);
    free(table);
}

/* Printing error message for allocating memory with corresponding general */
void allocation_error_print_general(char reference[512])
{
    fprintf(stderr, "Failed to allocate memory for %s.\n", reference);
    exit(-3);
}

/* Printing error message for allocating memory with corresponding ID */
void allocation_error_print_with_id(char reference[512], int i)
{
    fprintf(stderr, "Failed to allocate memory for %s %d.\n", reference, i);
    exit(-4);
}

