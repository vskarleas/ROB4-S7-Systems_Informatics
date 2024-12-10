#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>

#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 250

void send_message(int port, char *message, char *name)
{
    struct hostent *server;
    int socket_fd;
    struct sockaddr_in server_address;
    int n;

    // create socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET is the address family for IPv4, SOCK_STREAM is the socket type for TCP
    if (socket_fd < 0)
    {
        perror("ERROR opening the socket");
        exit(1);
    }

    // Get the server's address
    server = gethostbyname(name);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }

    // Set up the server's address
    bzero((char *)&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    // Copy the server's address to the server_address structure
    memcpy(&server_address.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("ERROR connecting");
        exit(1);
    }

    n = write(socket_fd, message, strlen(message)); // maybe add +1 to handle the case when buffer is longer than BUFFER_SIZE
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    // sleep(3);
    // Close the socket
    close(socket_fd);
}

// We use fgets to receive our name that we save in a buffer and send it to the server.
int main(int argc, char **argv)
{
    int n; // fd for file descriptor

    if (argc > 1)
    {
        fprintf(stderr, "Usage: You do not have the right to declare those parameters\n");
        exit(1);
    }

    // Receive the name for the person who we vote for and how many votes (+++) do we send. Votes are minimum 1 and maximum 5. The program verifies that this person exists in a list of presidents that we have to declare. A message is created with the protocol V_president-name_Number-of-votes.

    // Bellow we create the message that is sent to the server.

    char message[BUFFER_SIZE];
    char president_name[BUFFER_SIZE];
    int number_of_votes;

    bool repeater = true;

    printf("Enter the name of the president you want to vote for: ");
    if (fgets(president_name, BUFFER_SIZE, stdin) == NULL)
    {
        printf("Error reading input\n");
        exit(1);
    }

    // Remove newline character if present
    size_t len = strlen(president_name);
    if (len > 0 && president_name[len - 1] == '\n')
    {
        president_name[len - 1] = '\0';
    }

    // verifiyign that president_name is included in presidents list. Create this president list
    //  If not, print an error message and exit the program
    while (repeater)
    {
        if (strcmp(president_name, "Bush") == 0 || strcmp(president_name, "Obama") == 0 || strcmp(president_name, "Clinton") == 0 || strcmp(president_name, "Trump") == 0 || strcmp(president_name, "Biden") == 0)
        {
            repeater = false;
        }
        else
        {
            printf("\n%s is not in the list\n", president_name);
            printf("\nEnter the name of the president you want to vote for: ");
            if (fgets(president_name, BUFFER_SIZE, stdin) == NULL)
            {
                printf("Error reading input\n");
                exit(1);
            }

            len = strlen(president_name);
            if (len > 0 && president_name[len - 1] == '\n')
            {
                president_name[len - 1] = '\0';
            }
        }
    }

    printf("Enter the number of votes you want to give: ");
    if (scanf("%d", &number_of_votes) != 1)
    {
        printf("Error reading input\n");
        exit(1);
    }

    repeater = true;
    while (repeater)
    {
        if (number_of_votes < 1 || number_of_votes > 5)
        {
            printf("The number of votes must be between 1 and 5\n");
            printf("Enter the number of votes you want to give: ");
            if (scanf("%d", &number_of_votes) != 1)
            {
                printf("Error reading input\n");
                exit(1);
            }
        }
        else
        {
            repeater = false;
        }
    }

    // Create the message
    sprintf(message, "V_%s_%d", president_name, number_of_votes);
    printf("Sending message: %s\n", message);

    // send_message(atoi(argv[2]), message, argv[1]);
    send_message(32000, message, "localhost");

    return 0;
}