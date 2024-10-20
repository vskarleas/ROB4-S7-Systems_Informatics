#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "affiche.h"
#include "saisie.h"

int main(int argc, char **argv)
{

    double *coefficients;
    int degree;
    printf("======== Setting up the polynomial degree ========\n\n");
    // Set up the polynomial degree and coefficients.
    saisie_coeff(&coefficients, &degree);

    double x_value = 2.5;
    
    // Display the polynomial and its result at the given x value.
    affiche_polynome(degree, coefficients, x_value);

    return 0;
}