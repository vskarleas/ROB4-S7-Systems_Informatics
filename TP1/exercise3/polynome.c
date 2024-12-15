#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "affiche.h"
#include "error.h"

/* We retake the exercise 1. Here we expect to receive all the information we need to
create the polynome via arguments parsed on the command-line. We want simply once we detect
that an argument is --val to take the next argument of it as the degree and once we detect
the argumment --coeff to take the followign arguments as the coeeficienst as expected. We are
doing a treatment of errors if necessary */

int main(int argc, char **argv)
{
    double *coefficients = NULL;
    double *coeff_buffer = NULL; // Temporary buffer for coefficients
    int degree = -1;
    int coeff_count = 0;

    // bool coeff_flag = false; // To check if --coeff has been parsed

    bool val_parsed = false;    // To check if --val has been parsed
    bool coeff_parsed = false;  // To check if --coeff has been parsed
    bool formel_parsed = false; // To check if --formel has been parsed

    int i = 1; // Start from the second argument (skip the program name)
    while (i < argc)
    {
        if ((strcmp(argv[i], "--val") == 0) && val_parsed == false)
        {
            i++;
            val_parsed = true;

            // Test in case that --val is the end and so the following action ould provoke segmentation fault
            if (i >= argc)
            {
                fprintf(stderr, "Error: Degree (--val) was not provided.\n");
                exit(EXIT_FAILURE);
            }
            degree = atoi(argv[i]); // Parse the degree as an integer

            if (degree < 0)
            {
                fprintf(stderr, "Error: Degree must be a non-negative integer.\n");
                exit(EXIT_FAILURE);
            }

            // Now that we know the degree, we can allocate memory for the coefficients array
            coefficients = (double *)malloc((degree + 1) * sizeof(double)); // degree + 1 for x^0 to x^degree
            if (coefficients == NULL)
            {
                allocation_error_print_general("coefficients table (array)");
            }

            // If coefficients were parsed before --val, transfer them to the coefficients array since we have already saved then
            if (coeff_parsed)
            {
                for (int j = 0; j <= degree && j < coeff_count; j++)
                {
                    coefficients[j] = coeff_buffer[j];
                }

                // Printing an error/warning to deal with more coefficients than expected
                if (coeff_count > (degree + 1))
                {
                    fprintf(stderr, "Warning: More coefficients were provided than the degree. Ignoring the extra coefficients.\n");
                }

                free(coeff_buffer); // Free the temporary buffer !!! Literaly
            }
        }
        else if ((strcmp(argv[i], "--coeff") == 0) && coeff_parsed == false)
        {
            i++;
            coeff_parsed = true;

            // Test in case that --coeff is the end and so the following action ould provoke segmentation fault
            if (i >= argc)
            {
                fprintf(stderr, "Error: Coefficients (--coeff) were not provided.\n");
                exit(EXIT_FAILURE);
            }

            while (i < argc && argv[i][0] != '-') // Keep reading until the next flag (because all of them start with - or --) or end of arguments
            {
                coeff_count++;
                coeff_buffer = (double *)realloc(coeff_buffer, coeff_count * sizeof(double)); // realloc because we change the size dynamicly according to the coeff_count counter

                if (coeff_buffer == NULL)
                {
                    allocation_error_print_general("temporary coefficient buffer");
                }

                coeff_buffer[coeff_count - 1] = atof(argv[i]); // saving to the temporary buffer as real numbers in this case

                i++; // use of global i to get the next argument
            }

            if (val_parsed)
            {
                // Notoce that he passed less coefficients than expected
                if (coeff_count < (degree + 1))
                {
                    fprintf(stderr, "Warning: Less coefficients were provided than the degree. Program is terminating\n");
                    exit(EXIT_FAILURE);
                }

                // Notice that we passed more coefficients than expected
                if (coeff_count > (degree + 1))
                {
                    fprintf(stderr, "Warning: More coefficients were provided than the degree. Ignoring the extra coefficients.\n");
                }

                // Transfer coefficients from temporary buffer to coefficients array
                for (int k = 0; k <= degree; k++)
                {
                    coefficients[k] = coeff_buffer[k];
                }

                free(coeff_buffer); // Free the temporary buffer
            }

            i--; // Adjust for the next iteration in the while loop
        }
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {

            printf("Usage: %s --val <degree> --coeff <coefficients>\n", argv[0]);
            printf("Arguments:\n");
            printf("  --val <degree>    The degree of the polynomial (non-negative integer).\n");
            printf("  --coeff <coefficients>    The coefficients of the polynomial (real numbers).\n");
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argv[i], "--formel") == 0)
        {
            formel_parsed = true;
        }
        else
        {
            fprintf(stderr, "Error: Unexpected argument or argument wasn't found on the library: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }

        i++; // we move to the next argument
    }

    // Running background checks before we calculate the result
    if (argc > 1)
    {
        if (val_parsed)
        {
            if (coeff_parsed)
            {
                if (formel_parsed)
                {
                    affiche_polynome_formel(degree, coefficients, 2.5);
                }
                else
                {
                    affiche_polynome(degree, coefficients, 2.5);
                }
            }
            else
            {
                fprintf(stderr, "Error: Coefficients (--coeff) were not provided.\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "Error: Degree (--val) was not provided.\n");
            exit(EXIT_FAILURE);
        }

        free(coefficients);
    }
    else
    {
        fprintf(stderr, "Error: No arguments were provided.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}