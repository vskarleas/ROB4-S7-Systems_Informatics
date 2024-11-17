// #############################################################################
// # File logic.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdbool.h>

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

int command_launch_background(char **args);

/* It checks if the command has to be executed in the background */
bool run_in_background(char **args);

/* Executing stdout action to a file */
int command_launch_stdout(char **args);

/* Check if the command is followed by '|' character */
bool pipe_detection(char **args);

/* It checks if the stdout redirection operator is present in the arguments */
bool stdout_redirect_detection(char **args);

/* Builtin commands and system commands logic combined all together to an execution script that updates teh status of the main flag */
int execute(char **args);

/* It removes the stdout operator and the file name from the arguments */
void remove_stdout_operator(char **args, int index_file);

/* It provides the main syructure of the shell (read, parse, execute) */
void loop();

/* Executing a pipe instance */
int command_launch_pipe(char **args);

/* Check if the command is followed by '|' character */
bool pipe_detection(char **args);

#endif
