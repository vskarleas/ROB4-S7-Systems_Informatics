#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 250

// We use fgets to receive our name that we save in a buffer and send it to the server.
int main(int argc, char **argv)
{
    int socket_fd, port_number, n; // fd for file descriptor
    struct sockaddr_in server_address;
    struct hostent *server;
    char buffer[BUFFER_SIZE]; // Buffer to store the client's name

    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s hostname port file_name\n", argv[0]);
        exit(1);
    }
    port_number = atoi(argv[2]);

    // creating a socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET is the address family for IPv4, SOCK_STREAM is the socket type for TCP
    if (socket_fd < 0)
    {
        perror("ERROR opening the socket");
        exit(1);
    }

    // Get the server's address
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }

    // Set up the server's address
    bzero((char *)&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);

    // Copy the server's address to the server_address structure
    memcpy(&server_address.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("ERROR connecting");
        exit(1);
    }

    printf("Enter your First and Last name: ");
    fgets(buffer, BUFFER_SIZE, stdin); // Get the client's name

    //Taking the first name and last name in seperate variables from the buffer
    char first_name[sizeof(buffer)/2]; // We need to make sure that everything can fit in the buffer
    char last_name[sizeof(buffer)/2];
    // splitting the name into first name and last name using sscanf
    sscanf(buffer, "%s %s", first_name, last_name);

    // concatenating the reversed first name and last name
    sprintf(buffer, "%s %s", last_name, first_name);

    //opening a file using open() with name argv[3] in write mode and writing the reversed name
    int file = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(file < 0)
    {
        perror("Error opening the file");
        exit(1);
    }
    write(file, buffer, strlen(buffer));

    close(file); // Closing the file after writing the reversed name


    printf("You entered and sent to the server [%s:%s]: %s\n",argv[1], argv[2], buffer);

    //send the name to the server
    sleep(10);
    n = write(socket_fd, buffer, strlen(buffer)); // maybe add +1 to handle the case when buffer is longer than BUFFER_SIZE
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    // Close the socket
    close(socket_fd);
}