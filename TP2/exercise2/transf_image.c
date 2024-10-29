#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "image.h"
#include "transf_image.h"

void bruiter_image(image_t *img, unsigned int pourcent){
	//TODO
}





/* Récupère le temps courant en microsecondes */
unsigned long get_time() {
	struct timeval cTime;
	gettimeofday(&cTime, NULL);
	return ((unsigned long)(1000000*(cTime.tv_sec) + cTime.tv_usec));
}
