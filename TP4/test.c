// #############################################################################
// # File logic.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic.h"

/* This file is used for testing purposes only. Allows to test functiosn individualy */

int main(int argc, char **argv)
{

  char *line = read_line_v2();
  printf("Read line: %s\n", line);

  int arg_count = 0;
  int semicolons = 0;

  char **arguments = parse_line(line, &arg_count, &semicolons);

  // int i = 0;
  // while(arguments[i] != NULL)
  // {
  //   printf("Argument %d: %s\n",i+1, arguments[i]);
  //   i++;
  // }

  for (int i = 0; i < arg_count; i++)
  {
    printf("Argument %d: %s\n", i + 1, arguments[i]);
  }
  

  return EXIT_SUCCESS;
}