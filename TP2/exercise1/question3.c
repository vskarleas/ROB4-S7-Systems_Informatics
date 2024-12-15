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

void execute_command(char *command, char **args)
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
        if (execvp(command, args) == -1)
        {
            perror("Error while executing command");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS); // declare that this child is finished
    }
}

/* Programme équivalent à la commande shell who & ps & ls−l sans utiliser
system() (les commandes séparées par « & » s’exécutent en parallèle). */
int main(int argc, char **argv)
{
    int status = 0;

    // Execute the desired commands in parallel as different forks
    execute_command("who", (char*[]){"who", NULL});
    execute_command("ps", (char*[]){"ps", NULL});
    execute_command("ls", (char*[]){"ls", "-l", NULL});

    // Wait for all child processes to finish
    while ((waitpid(-1, &status, 0)) > 0); //waitpid(-1, &status, 0) == wait(&status) [page 34 course 2]

    return 0;
}
