#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	if (argc < 2)
	{
		fprintf(stderr, "./server <numport>\n");
		fprintf(stderr, "ex: ./server 32000\n");
		return 1;
	}

	// 1) on crée la socket, SOCK_STREAM signifie TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //123.123.123.123
	if (sockfd < 0)
	{
		fprintf(stderr, "Impossible d'ouvrir la socket.\n");
		return 1;
	}

	// 2) on réclame au noyau l'utilisation du port passé en paramètre
	// INADDR_ANY dit que la socket va être affectée à toutes les interfaces locales

	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; // we add any port that is available
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		fprintf(stderr, "Impossible de faire l'appel système bind().\n");
		return 1;
	}

	// On commence à écouter sur la socket. Le 5 est le nombre max
	// de connexions pendantes

	printf("Waiting for data. Connection succeeded...\n");

	// We want to include a fork so that we make the server directly available even
	// if the client that sent data has not finished its child process et. That way
	// when we have another client, then we can continue to listen for more clients.
	// We will use the fork() function to create a new process that will handle the
	// new client's connection.
	// The fork() function returns -1 if an error occurred, and 0 in the child process.
	// In the parent process, fork() returns the process ID of the child process.

	listen(sockfd, 5);

	while (1)
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
			// Child process
			close(sockfd); // Close the listening socket in the child. We are not onliged to use this

			bzero(buffer, 256);
			n = read(newsockfd, buffer, 255);
			if (n < 0)
			{
				fprintf(stderr, "Impossible de faire l'appel système read().\n");
				close(newsockfd);
				exit(1);
			}

			printf("Received packet from %s:%d\nData: [%s]\n\n",
				   inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);

			close(newsockfd);
			exit(0); // Exit the child process
		}
		else // Parent process
		{
			close(newsockfd); // Close the connected socket in the parent

            // We have to use waitpid in order to have only one process server when ./server is running. For now we observe two processes at a time.
			waitpid(pid, NULL, 0); // Wait for the child process to finish
		}
	}

	// listen(sockfd, 5);
	// while (1)
	// {
	// 	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	// 	if (newsockfd < 0)
	// 	{
	// 		fprintf(stderr, "Impossible de faire l'appel système accept().\n");
	// 		return 1;
	// 	}

	// 	bzero(buffer, 256);
	// 	n = read(newsockfd, buffer, 255);
	// 	if (n < 0)
	// 	{
	// 		fprintf(stderr, "Impossible de faire l'appel système read().\n");
	// 		return 1;
	// 	}

	// 	printf("Received packet from %s:%d\nData: [%s]\n\n",
	// 		   inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);

	// 	close(newsockfd);
	// }

	close(sockfd);
	return 0;
}
