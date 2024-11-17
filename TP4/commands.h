// #############################################################################
// # File commands.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef _COMMANDS_H_
#define _COMMANDS_H_

extern int (*builtin_func[])(char **);

/* Implementing here builtin commonds for the Shelly software. This list is not 
   exausted but it gives a general idea for this procedure */

int command_cd(char **args);
int command_help(char **args);
int command_exit(char **args);
int command_pwd(char **args);
int command_date(char **args);
int command_echo(char **args);
int command_cat(char **args);
int command_wc(char **args);

extern const char *builtin_str[];

#endif