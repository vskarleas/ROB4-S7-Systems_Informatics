#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* The main function that prints the command-line arguments in reverse order. */
int main(int argc, char **argv)
{
    for (int i = argc - 1; i >= 1; i--)
    {
        printf("Parameter %d: %s \n",i, argv[i]);
    }
}