// #############################################################################
// # File question2.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // getpid () , gettpid () , getuid () , getgid ()
#include <sys/types.h> // pid_t , uid_t , gid_t

/* En utilisant la fonction system() , écrivez un programme permettant d’ouvrir avec le pro-
gramme emacs un fichier dont le nom a été passé en argument d’entrée de l’exécutable
et qui rend ensuite la main à l’utilisateur. */

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "More arguments passed than expected\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }
    else if (argc == 1)
    {
        fprintf(stderr, "No filename provided\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }
    else
    {
        char *command = malloc(strlen("emacs ") + strlen(argv[1]) + 1); // Allocate memory for the command string + 1 for the null terminator \0
        strcpy(command, "emacs ");
        strcat(command, argv[1]); // concantenation

        if (!system(command))
        {
            printf("( le fichier %s etait ouvert dans emacs)\n", argv[1]); //message from the TP example
        }
        else
        {
            printf("Error while opening the file %s on emacs", argv[1]);
        }

        free(command);
    }

    return 0; // Exit the parent process
}
