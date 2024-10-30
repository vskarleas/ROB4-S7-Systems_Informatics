#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "image.h"
#include "transf_image.h"
#include <time.h>

int random_number(int min, int max)
{
	return (rand() % (max - min + 1) + min); // Generates a number between min and max
}

/* Le principe du bruitage est simple : pour
chaque pixel de l’image, une valeur aléatoire est tirée dans l’intervalle [0, 100]. Si cette
valeur est inférieure au pourcentage fournit comme argument d’entrée de la fonction, le
pixel prend une valeur aléatoire dans l’intervalle de niveau de gris de l’image.
*/
void bruiter_image(image_t *img, unsigned int pourcent)
{
	srand(time(NULL)); // should bhe called only once

	for (int i = 0; i < img->nx; i++)
	{
		for (int j = 0; j < img->ny; j++)
		{
			int random = random_number(0, 100);
			if (random < pourcent)
			{
				VAL(img, i, j) = random_number(0, img->nb_ng);
			}
		}
	}
}

void bruiter_image_zone(image_t *img, unsigned int pourcent, int x1, int y1, int collones, int lignes)
{

	// Calculating x2 and y2
	int x2 = x1 + collones;
	int y2 = y1 + lignes;

	// Checking if the area is out of the image limits
	if (x2 > img->nx)
	{
		x2 = img->nx;
	}
		
	if (y2 > img->ny)
	{
		y2 = img->ny;
	}
		
	for (int i = x1; i < x2; i++)
	{
		for (int j = y1; j < y2; j++)
		{
			int random = random_number(0, 100);
			if (random < pourcent)
			{
				VAL(img, i, j) = random_number(0, img->nb_ng);
			}
		}
	}

	for (int i = x1; i < x2; i++)
	{
		for (int j = y1; j < y2; j++)
		{
			int random = random_number(0, 100);
			if (random < pourcent)
			{
				VAL(img, i, j) = random_number(0, img->nb_ng);
			}
		}
	}
}

/* Récupère le temps courant en microsecondes */
unsigned long get_time()
{
	struct timeval cTime;
	gettimeofday(&cTime, NULL);
	return ((unsigned long)(1000000 * (cTime.tv_sec) + cTime.tv_usec));
}
