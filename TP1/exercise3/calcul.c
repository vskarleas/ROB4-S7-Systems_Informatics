#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "calcul.h"
#include "error.h"


/* Function to evaluate a polynomial with a given degree and coefficients at a given x value. */
double eval_polynome(int degree, double *coefficients, double x_value)
{
    //Preliminary tests as described to the TP's subjects
    if (coefficients == NULL || degree < 0)
    {
        fprintf(stderr, "Degree is not positive or NULL or the real numbers tabe is NILL \n");
        exit(1);
    }

    // Evaluate the polynomial by summing up the product of coefficients and powers of x.
    double result = 0;
    for (int i = 0; i <= degree; i++)
    {
        result += coefficients[i] * pow(x_value, i);
    }
    return result;
}