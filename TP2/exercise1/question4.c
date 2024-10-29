// #############################################################################
// # File question3.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // getpid () , gettpid () , getuid () , getgid ()
#include <sys/types.h> // pid_t , uid_t , gid_t
#include <sys/wait.h>  // waitpid()

void execute_command(char *command, char **args, pid_t *command_pid, int *status)
{
    *command_pid = fork();
    if (*command_pid == -1)
    {
        perror("Error while forking the process");
        exit(EXIT_FAILURE);
    }
    else if (*command_pid == 0)
    {
        // Child process: Execute the command
        if (execvp(command, args) == -1)
        {
            perror("Error while executing command");
            exit(EXIT_FAILURE);
        }
    }

    waitpid(*command_pid, status, 0); // Wait for the current command and it's process to finish
}

/* Programme équivalent à la commande shell who & ps & ls−l sans utiliser
system() (les commandes séparées par « & » s’exécutent en parallèle). */
int main(int argc, char **argv)
{
    int status = 0;
    pid_t pid;

    // Execute the desired commands in succesive mode
    execute_command("who", (char*[]){"who", NULL}, &pid, &status);
    execute_command("ps", (char*[]){"ps", NULL}, &pid, &status);
    execute_command("ls", (char*[]){"ls", "-l", NULL}, &pid, &status);
   

    return 0;
}
