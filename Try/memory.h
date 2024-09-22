// #############################################################################
// # File memory.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// ############################################################################# 

#ifndef H_MEMORY
#define H_MEMORY

/* Freeing a 2D array */
void free_2d(int **table, int n);

/* Printing error message for allocating memory with corresponding general */
void allocation_error_print_general(char reference[512]);

/* Printing error message for allocating memory with corresponding ID */
void allocation_error_print_with_id(char reference[512], int i);

#endif