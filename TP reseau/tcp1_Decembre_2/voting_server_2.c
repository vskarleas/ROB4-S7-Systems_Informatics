#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include <sys/shm.h> // Include for shared memory

int server_initialisation(int port) //it returns the socket file descriptor
{
    int sockfd;
    struct sockaddr_in serv_addr;
    // 1) on crée la socket, SOCK_STREAM signifie TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 123.123.123.123
    if (sockfd < 0)
    {
        fprintf(stderr, "Impossible d'ouvrir la socket.\n");
        return 1;
    }

    // 2) on réclame au noyau l'utilisation du port passé en paramètre
    // INADDR_ANY dit que la socket va être affectée à toutes les interfaces locales

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // we add any port that is available
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Impossible de faire l'appel système bind().\n");
        return 1;
    }

    // On commence à écouter sur la socket. Le 5 est le nombre max
    // de connexions pendantes
    printf("Waiting for data. Connection succeeded...\n");

    return sockfd;
}

void get_message(int copied_socket, char *buffer, int main_socket, struct sockaddr_in cli_addr, int *oui_count, int *non_count)
{
    int n;
    close(main_socket); // Close the listening socket in the child. We are not obliged to use this

    bzero(buffer, 256);
    n = read(copied_socket, buffer, 255);
    if (n < 0)
    {
        fprintf(stderr, "Impossible de faire l'appel système read().\n");
        close(copied_socket);
        exit(1);
    }

    char vote_type[10];
    if (sscanf(buffer, "V_%s", vote_type) == 1)
    {
        if (strcmp(vote_type, "OUI") == 0)
        {
            (*oui_count)++;
            printf("Received a vote for OUI\n\n");
        }
        else if (strcmp(vote_type, "NON") == 0)
        {
            (*non_count)++;
            printf("Received a vote for NON\n\n");
        }
    }
    else
    {
        printf("Received packet from %s:%d\nData: [%s]\n\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);
    }

    printf("Current OUI count: %d\n", *oui_count);
    printf("Current NON count: %d\n", *non_count);

    close(copied_socket);
    exit(0); // Exit the child process
}

void server_loop(int sockfd, struct sockaddr_in cli_addr, socklen_t clilen, char *buffer, int *oui_count, int *non_count)
{
    int newsockfd;

    while (true)
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            fprintf(stderr, "Impossible de faire l'appel système accept().\n");
            continue; // Continue to next iteration instead of exiting
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Impossible de faire un fork().\n");
            close(newsockfd);
            continue; // Continue to next iteration instead of exiting
        }

        // If pid is 0, then we are in the child process
        if (pid == 0)
        {
            get_message(newsockfd, buffer, sockfd, cli_addr, oui_count, non_count);
        }
        else // Parent process
        {
            close(newsockfd); // Close the connected socket in the parent

            // We have to use waitpid in order to have only one process server when ./server is running. For now we observe two processes at a time.
            waitpid(pid, NULL, 0); // Wait for the child process to finish
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in cli_addr;

    if (argc < 2)
    {
        fprintf(stderr, "./server <numport>\n");
        fprintf(stderr, "ex: ./server 32000\n");
        return 1;
    }

    // Create shared memory for vote counts
    int shm_id_oui = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int shm_id_non = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shm_id_oui < 0 || shm_id_non < 0)
    {
        fprintf(stderr, "Failed to create shared memory.\n");
        return 1;
    }

    int *oui_count = (int *)shmat(shm_id_oui, NULL, 0); //shared memory for OUI count
    int *non_count = (int *)shmat(shm_id_non, NULL, 0); //shared memory for NON count
    if (oui_count == (int *)-1 || non_count == (int *)-1)
    {
        fprintf(stderr, "Failed to attach shared memory.\n");
        return 1;
    }

    *oui_count = 0; // Initialize all votes to 0
    *non_count = 0;

    sockfd = server_initialisation(atoi(argv[1]));
    listen(sockfd, 5);
    server_loop(sockfd, cli_addr, clilen, buffer, oui_count, non_count); // we will loop indefinitely until we manually stop the server
    close(sockfd);

    // Detach and remove shared memory
    shmdt(oui_count);
    shmdt(non_count);
    shmctl(shm_id_oui, IPC_RMID, NULL);
    shmctl(shm_id_non, IPC_RMID, NULL);

    return 0;
}