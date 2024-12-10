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

    char buffer[BUFFER_SIZE]; // Buffer to store the client's name

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    printf("Enter your First and Last name: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        printf("Error reading input\n");
        exit(1);
    }

    char first_name[sizeof(buffer) / 2]; // We need to make sure that everything can fit in the buffer
    char last_name[sizeof(buffer) / 2];
    // splitting the name into first name and last name using sscanf
    sscanf(buffer, "%s %s", first_name, last_name);

    // Remove newline character if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    char extra_message[100] = "has joined the chat";
    char buffer_connection_message[350];
    strcpy(buffer_connection_message, buffer);        // Copy str1 into result
    strcat(buffer_connection_message, " ");           // Add a space to result
    strcat(buffer_connection_message, extra_message); // Concatenate str2 to result

    send_message(atoi(argv[2]), buffer_connection_message, argv[1]); // argv[2] is the port number and argv[1] is the server's hostname

    // Infinite loop that keep sending messages until it receves the keyword stop. It uses the function send_message() defined above.

    printf("You are now connected to the chat %s.\n", first_name); // Print a message to indicate the connection
    printf("Enter 'stop' to stop the client. Chat with others.\n");
    int i = 1;
    while (true)
    {
        printf("Message #%d: ", i);
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            printf("Error reading message\n");
            exit(1);
        }
        if (strcmp(buffer, "stop\n") == 0)
        {
            break;
        }

        // Remove newline character if present
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        send_message(atoi(argv[2]), buffer, argv[1]);
        i++;
    }

    return 0;
}