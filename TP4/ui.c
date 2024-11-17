// #############################################################################
// # File ui.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "ui.h"

/* Declaring some ASCI colors for UI porpuses */
void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void green()
{
    printf("\033[1;32m");
}

void blue()
{
    printf("\033[1;34m");
}

void cyan()
{
    printf("\033[1;36m");
}

void purple()
{
    printf("\033[1;35m");
}

void white()
{
    printf("\033[1;37m");
}

void reset()
{
    printf("\033[0m");
}

/* String concantentation for chidr error message creation */
char *chdir_error_message(char *path)
{
    char *part1_message = "chdir() to ";
    char *part2_message = " failed";
    char *error_message = malloc(strlen(part1_message) + strlen(part2_message) + strlen(path) + 1);
    strcpy(error_message, part1_message);
    strcat(error_message, path);
    strcat(error_message, part2_message);

    return error_message;
}

/* Date and time for shell start */
void print_time()
{
    // Extracting time info data
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    printf("%02d/%02d/%04d %02d:%02d\n",
           currentTime->tm_mday, currentTime->tm_mon + 1, currentTime->tm_year + 1900,
           currentTime->tm_hour, currentTime->tm_min);
}
