// #############################################################################
// # File ui.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef _UI_H_
#define _UI_H_

/* Declaring some ASCI colors for UI porpuses */
void red();
void yellow();
void green();
void blue();
void cyan();
void purple();
void white();
void reset();

/* String concantentation for chidr error message creation */
char *chdir_error_message(char *path);

/* Date and time for shell start */
void print_time();

#endif