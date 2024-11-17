// #############################################################################
// # File shell.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdlib.h>

#include "logic.h"

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}