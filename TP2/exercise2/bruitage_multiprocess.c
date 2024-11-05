#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "transf_image.h"
#include <unistd.h>	   // getpid () , gettpid () , getuid () , getgid ()
#include <sys/types.h> // pid_t , uid_t , gid_t
#include <sys/wait.h>  // waitpid()
#include <sys/mman.h>  // mmap()
#include <time.h>	   // time()

void display_usage()
{
	printf("\nUsage : ./question2 nom_fichier_origine --bruit pourcentage nom_fichier_destination\n\n");
}

void execute_bruitage(image_t *shared_img, unsigned int pourcent, int x1, int y1, int collones, int lignes)
{
	pid_t command_pid = fork();
	if (command_pid == -1)
	{
		perror("Error while forking the process");
		exit(EXIT_FAILURE);
	}
	else if (command_pid == 0)
	{
		// Child process: Execute the command
		bruiter_image_zone(shared_img, pourcent, x1, y1, collones, lignes);
		exit(EXIT_SUCCESS); //declare that this child is finished
	}

}

int main(int argc, char **argv)
{

	image_t *img = NULL;
	unsigned long t0, tf;
	unsigned int pcent;

	/* Test des arguments du main */
	if ((argc != 5) || strcmp(argv[2], "--bruit"))
	{
		display_usage();
		return -1;
	}

	/* Récupération du pourcentage de bruit */
	pcent = atoi(argv[3]);
	if ((pcent > 100) || (pcent < 0))
	{
		display_usage();
		return -1;
	}

	/* Chargement de l'image d'origine */
	img = charger_image_pgm(argv[1]);
	if (!img)
	{
		display_usage();
		return -1;
	}

	/* Compteur de temps initial */
	t0 = get_time();
	int status = 0;

	image_t *shared_img = dupliquer_vers_mmap_anon(img);
	if (shared_img == NULL)
	{
		fprintf(stderr, "Error creating shared memory image\n");
		return -1;
	}

	// Define segment dimensions
	int segments_x = 2;
	int segments_y = 2;
	int segment_width = img->nx / segments_x;
	int segment_height = img->ny / segments_y;

	srand(time(NULL)); // should bhe called only once

	for (int k = 0; k < 2; k++)
	{
		for(int l = 0; l < 2; l++)
		{
			execute_bruitage(shared_img, pcent, k * segment_width, l * segment_height, segment_width, segment_height);
		}
	}

	/* REMARKS ON PROCESSING TIME 
	Here are the results:

	(base) vasilisskarleas@macbookpro exercise2 % ./question2 images/12vaches.pgm --bruit 30 images/12vaches_bruit.pgm
	Operation realisee en 96842 microsecondes.
	(base) vasilisskarleas@macbookpro exercise2 % ./question2_multiprocess images/12vaches.pgm --bruit 30 images/12vaches_bruit_multiprocess.pgm
	Operation realisee en 57644 microsecondes.

	We are about at 48% less processing time for this multi-process version.

	We can notice that if we want to do writings/reads in parallel on the same file in the system
	(like an image), we cannot do it if we had done a simple malloc as usual. We must use mmap()
	to create a shared memory area between processes. This is what we did here, while declaring
	that it is anonymous (so universal) with write and read rights respectively. Thus, we can call
	the noise of the 4 zones in parallel and of course reduce the execution time.

	*/

    /* Wait for all the processes before continue */
	while ((waitpid(-1, &status, 0)) > 0); // or we can use wait(NULL) to wait for any child process

	



	/* Compteur de temps final */
	tf = get_time();
	printf("Operation realisee en %lu microsecondes.\n", (tf - t0));

	/* Sauvegarde de l'image */
	sauver_image_pgm(argv[4],shared_img);

	/* Destruction de l'image en local et en memoire */
	detruire_image(img);
	detruire_image_mmap(shared_img);

	return 0;
}
