// #############################################################################
// # File logic.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef _LOGIC_H_
#define _LOGIC_H_

/* Reads a line in a standard mode */
char *read_line_v1();

/* Improuved version of the function read_line_v1 that uses the getline integrated function */
char *read_line_v2();

/* It divides the line that was read in arguments */
char **parse_line(char *line, int *arg_count);

/* It executes a command by splitting it into arguments and executing the first one */
int command_launch(char **args);

/* Builtin commands and system commands logic combined all together to an execution script that updates teh status of the main flag */
int execute(char **args);

/* It provides the main syructure of the shell (read, parse, execute) */
void loop();

#endif
