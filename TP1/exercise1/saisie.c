#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "error.h"

/* Function to prompt the user to enter a real number. */
void saisie_valeur_reelle(double *value)
{
    printf("Enter a real number: ");
    scanf("%lf", value);
}

/* Function to prompt the user to enter a positive integer (or 0 is accepted as well). */
void saisie_valeur_entiere(int *value)
{
    int input;

    do
    {
        printf("Enter a positive integer: ");
        scanf("%d", &input);
    } while (input <= 0);
    printf("\n"); // To make the output clearer.

    *value = input;
}

/* We ask the user for the coefficients of the polynomial. */
void saisie_coeff(double **tab , int *n)
{
    // Prompt the user to enter the degree of the polynomial.
    saisie_valeur_entiere(n);

    // Allocate memory for the coefficients array.
    *tab = (double *)malloc((*n + 1) * sizeof(double)); // +1 for the constant term. This is important!! We do a casting for double
    if (*tab == NULL)
    {
        allocation_error_print_general("coefficients table (array)");
    }

    // Prompt the user to enter the coefficients of the polynomial.
    printf("======== Setting up the polynome ========\n\n");
    for (int i = 0; i <= *n; i++)
    {
        printf("Coefficient pour x^%d : ", i);
        saisie_valeur_reelle(&(*tab)[i]);
    }
    printf("\n"); // To make the output clearer.
}