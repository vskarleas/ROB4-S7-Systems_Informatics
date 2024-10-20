#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "affiche.h"
#include "calcul.h"

/* Function to display the polynomial with a given degree and coefficients at a given x value. */
void affiche_polynome(int degree, double *coefficients, double x_value)
{
    double result = eval_polynome(degree, coefficients, x_value);
    printf("Polynomial coefficients: ");

    // Print the polynomial coefficients in reverse order.
    for (int i = degree; i > 0; i--)
    {
        printf("%.2f * x^%d +", coefficients[i], i);
    }
    printf("%.2f * x^%d \n", coefficients[0], 0);

    // Print the result of the polynomial evaluation at the given x value.
    printf("\nResult at x = %.2lf: %.2lf\n", x_value, result);
}
