// #############################################################################
// # File commands.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "commands.h"
#include "ui.h"
#include "macros.h"

/* Array of function pointers that includes the builtin declaration of functions found at builtin_str declared on macros.h  */
int (*builtin_func[])(char **) = {
    &command_cd,
    &command_help,
    &command_exit,
    &command_pwd,
    &command_date,
    &command_echo,
    &command_cat,
    &command_wc};

/* Implementing here builtin commonds for the Shelly software. This list is not
   exausted but it gives a general idea for this procedure */

/* Declaration of the cd command */
int command_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Error: Expected the argument \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0) // the execution of change directory is happening here and we use the return status to decide if the operation was successful or not
        {

            char *error_message = chdir_error_message(args[1]);
            perror(error_message);
        }
    }
    return 1;
}

/* Declaration of the pwd command */
int command_pwd(char **args)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("Error: Failed to get the current working directory.");
    }
    return 1;
}

/* Declaration of the exit command */
int command_exit(char **args)
{
    return 0;
}

/* Declaration of the help command */
int command_help(char **args)
{
    green();
    printf("This is a configurable shell program that is called Shelly.\n");
    reset();
    printf("The following commands are built in:\n");

    int i;
    for (i = 0; i < NUM_BUILTINS; i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("\nUse the man command for information on other programs.\n");
    yellow();
    printf("Feel free to clone its repository and modify its code to perfom the tasks that you wish. It's easy even to integrate commands that do not exist by default in your OS since Shelly is built exclusively on C. The repository of Shelly is available at https://github.com/vskarleas/ROB3-S7-Shelly \n");
    reset();
    return 1;
}

/* Declaration of the date command */
int command_date(char **args)
{
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    printf("%02d/%02d/%04d %02d:%02d\n",
           currentTime->tm_mday, currentTime->tm_mon + 1, currentTime->tm_year + 1900,
           currentTime->tm_hour, currentTime->tm_min);

    return 1;
}

/* Declaration of the echo command */
int command_echo(char **args)
{
    int i = 1; // start from the second argument
    while (args[i] != NULL)
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return 1;
}

/* Declaration of the cat command */
int command_cat(char **args)
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    if (args[1] == NULL) // first check for the existence of the argument
    {
        fprintf(stderr, "Error: Expected the argument \"cat\"\n");
    }
    else
    {
        file = fopen(args[1], "r");
        if (file == NULL)
        {
            perror("Error: Failed to open the file");
        }
        else
        {
            while (fgets(line, MAX_LINE_LENGTH, file))
            {
                printf("%s", line);
            }
            fclose(file);
        }
    }

    return 1;
}

/* Declaration of the wc command */
int command_wc(char **args)
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int count = 0;
    if (args[1] == NULL) // first check for the existence of the argument
    {
        fprintf(stderr, "Error: Expected the argument \"wc\"\n");
    }
    else
    {
        file = fopen(args[1], "r");
        if (file == NULL)
        {
            perror("Error: Failed to open the file");
        }
        else
        {
            while (fgets(line, MAX_LINE_LENGTH, file))
            {
                count++;
            }
            printf("The number of lines in the file is: %d\n", count);
            fclose(file);
        }
    }

    return 1;
}

/*
  List of builtin commands, followed by their corresponding functions.
  This list follows exactly the ordering used at int (**builtin_func[])(char **) 
  that can be found at commands.c file.
 */
const char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "pwd",
  "date",
  "echo",
  "cat",
  "wc"
};