#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Version 1 of the program that converts all arguments to double and adds them up. */
double version_1(char **argv, int argc)
{
    double sum = 0;
    for (int i = 1; i < argc; i++)
    {
        sum += atof(argv[i]); // Convert string to double. If not a number, atof returns 0. 
    }
    return sum;
}


/* Version 2 of the program that checks each argument to see if it is a valid number. 
If it is not, it prints out an error message and exits the program. */
double version_2(char **argv, int argc)
{
    double sum = 0;
    for (int i = 1; i < argc; i++)
    {
        char *endptr;
        double number = strtod(argv[i], &endptr); // Convert string to double and check for errors. 
        if (*endptr != '\0')
        {
            fprintf(stderr, "Argument %d is not a number. Please parse only number as arguments\n", i);
            exit(1);
        }
        sum += number;
    }
    return sum;
}


/* Main program that additions the real numbers given as command-line arguments. 
If it detctes that an argument is not a number, then it prints out un error since 
this is not the intented use of the program */
int main(int argc, char **argv)
{
    printf("Sum of the real numbers: %.2lf\n", version_1(argv, argc));
    printf("Sum of the real numbers (optimized version): %.2lf\n", version_2(argv, argc)); // Use the optimized version.
    return 0;
}
