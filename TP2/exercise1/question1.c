// #############################################################################
// # File question1.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// ############################################################################# 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // getpid () , gettpid () , getuid () , getgid ()
#include <sys/types.h> // pid_t , uid_t , gid_t

/* un programme affichant son PID puis utilisant des appels à fork () dans une
boucle for pour générer cinq processus enfant, puis se terminer. */
int main(int argc, char **argv)
{
    pid_t pid;
    int i;
    printf("Je suis le parent , PID %d\n------------\n", getpid());
    for (i = 0; i < 5; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            printf("Child %d : My PID is %d\n", i+1, getpid());
            exit(0);  // Exit the child process when it's done otherwise it will create more child processes
        }
    }

    return 0;  // Exit the parent process

}