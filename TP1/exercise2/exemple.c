#include <stdio.h>

void somme_n(void)
{

    int n_max;

    printf("calcule la somme des n premiers entiers, entrez n : ");
    scanf("%d", &n_max);

    int somme = 0;

    for (int i = 0; i <= n_max; i++)
        somme += i;

    printf("la somme est %d\n", somme);
}

void somme_n_v2(int *n_max)
{
    printf("calcule la somme des n premiers entiers, entrez n : ");
    scanf("%d", n_max);

    int somme = 0;

    for (int i = 0; i <= *n_max; i++)
        somme += i;

    printf("la somme est %d\n", somme);
}

int main(void)
{

    int somme = 0;

    somme_n();
    somme_n_v2(&somme);
    return 0;
}
