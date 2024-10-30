#ifndef TRANSF_IMAGE
#define TRANSF_IMAGE

#include "image.h"

void bruiter_image(image_t *img, unsigned int pourcent);

void bruiter_image_zone(image_t *img, unsigned int pourcent, int x1, int y1, int collones, int lignes);

unsigned long get_time();
#endif
