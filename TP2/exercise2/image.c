#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include "image.h"

/* Alloue et initialise une structure image_t (vide) sur le tas
   et renvoie un pointeur vers elle */
image_t *creer_image()
{

  image_t *p = (image_t *)malloc(sizeof(image_t));

  p->nx = 0;
  p->ny = 0;
  p->nb_ng = 0;
  p->buff = NULL;

  return p;
}

/* Configure une structure image_t *p_im (précédemment allouée
   avec creer_image) pour stocker une image de taille nx par
   ny avec nb_ng niveau de gris, en allouant la mémoire pour
   stocker les pixels.
   Renvoie un pointeur sur l'image_t */
image_t *allouer_image(image_t *p_im,
                       unsigned int nx,
                       unsigned int ny,
                       unsigned int nb_ng)
{

  p_im->nx = nx;
  p_im->ny = ny;
  p_im->nb_ng = nb_ng;
  p_im->buff = (unsigned char *)calloc(nx * ny, sizeof(char));

  return p_im;
}

/* Créer (sur le tas) une copie de l'image *src.
   Renvoie un pointeur vers la copie. */
image_t *dupliquer_image(image_t *src)
{

  image_t *dst = creer_image();

  dst->nx = src->nx;
  dst->ny = src->ny;
  dst->nb_ng = src->nb_ng;
  dst->buff = (unsigned char *)malloc(src->nx * src->ny);
  memcpy(dst->buff, src->buff, src->nx * src->ny);
  return dst;
}

/* Il stocke l’image et ses données dans une projection mmap anonyme partagée
et non dans des espaces alloués par malloc. Attention, il y a deux choses à copier : la structure image_t et le buffer contenant les données de l’image.
On souhaite que ces deux choses soient stockées dans l’espace réservé par mmap, de facon contigue. Prenez le en
compte pour demander une projection mémoire de taille suffisante. */

image_t *dupliquer_vers_mmap_anon(image_t *src)
{
  int size = sizeof(image_t) + src->nx * src->ny * sizeof(unsigned char); // Images data and its size are taken into account

  image_t *dst = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  if (dst == MAP_FAILED)
  {
    fprintf(stderr, "Error while creating the projection mmap\n");
    free(dst);

    return NULL; //important to return NULL to avoid memory leaks since this function is a type image_t *
  }

  memcpy(dst, src, sizeof(image_t)); // Structure data

  /* We need to declare what is the starting of the buffer in the mmap reserved memory. 
  By taking the dst addresse + sizeof(image_t) we are pointing to the start of the buffer 
  which is an unsigned char. That is the reson why we are doing a cast to unsigned char *
  */
  dst->buff = (unsigned char *)(dst + 1);
  
  memcpy(dst->buff, src->buff, src->nx * src->ny); // Pixel data



  return dst;
}

/* Détruis une image, en libérant la mémoire des pixels puis
   celle de la structure. */
void detruire_image(image_t *p)
{

  free(p->buff);
  free(p);
}

void detruire_image_mmap(image_t *p)
{
  size_t size = sizeof(image_t) + p->nx * p->ny * sizeof(unsigned char);
  munmap(p, size);
}

#define TMP_STR_SIZE 64 // Limite du nom des fichiers images

/* Lis le fichier nom_fichier et le charge dans un nouvel
   image_t.
   Renvoie un pointeur vers l'image_t, ou NULL en cas d'erreur. */
image_t *charger_image_pgm(char *nom_fichier)
{
  FILE *f;
  image_t *img;
  char tmp_str[TMP_STR_SIZE];

  f = fopen(nom_fichier, "r");

  if (!f)
  {
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
    return NULL;
  }

  if (!(img = creer_image()))
    return NULL;

  fgets(tmp_str, TMP_STR_SIZE, f);

  if (strcmp(tmp_str, "P5\n"))
  {
    fprintf(stderr, "format fichier non pgm (P5)\n");
    return NULL;
  }

  fgets(tmp_str, TMP_STR_SIZE, f);

  if (sscanf(tmp_str, "%d %d\n", &(img->nx), &(img->ny)) != 2)
  {
    fprintf(stderr, "format fichier non pgm\n");
    return NULL;
  }

  fgets(tmp_str, TMP_STR_SIZE, f);

  if (sscanf(tmp_str, "%d\n", &(img->nb_ng)) != 1)
  {
    fprintf(stderr, "format fichier non pgm\n");
    return NULL;
  }

  img->buff = (unsigned char *)malloc(img->nx * img->ny);

  if (fread(img->buff, img->nx, img->ny, f) != img->ny)
  {
    fprintf(stderr, "fichier image imcomplet!\n");
    return NULL;
  }
  fclose(f);
  return img;
}

/* Sauvegarde l'image img dans le fichier nom_fichier.
   Renvoie 0 en cas de succès ou 1 en cas d'erreur d'ouverture du fichier. */
int sauver_image_pgm(char *nom_fichier, image_t *img)
{
  FILE *f;

  f = fopen(nom_fichier, "w");

  if (!f)
  {
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
    return 1;
  }

  fprintf(f, "P5\n");
  fprintf(f, "%d %d\n", img->nx, img->ny);
  fprintf(f, "%d\n", img->nb_ng);

  fwrite(img->buff, img->nx, img->ny, f);
  fclose(f);
  return 0;
}
