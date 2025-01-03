#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double *gen_n_doubles(int n)
{

  // Allouer de la memoire
  double *x = (double *)malloc(n * sizeof(double));

  // Initialise le generateur de nombres pseudo-aleatoires
  srand(time(NULL));

  for (int i = 0; i < n; i++)
  {
    // Genere un reel compris entre 0 et 1
    *(x + i) = (double)(rand() / (RAND_MAX));
  }
  return x;
}

int main(void)
{

    // Generer 100 doubles
    double *nombres = gen_n_doubles(100);
    // Les afficher :
    int i;
    for (i = 0; i < 100; i++)
      printf("%d | %f\t", i, nombres[i]);
    printf("\n");

    free(nombres); // Libérer la memoire allouée
  
  return 0;
}
