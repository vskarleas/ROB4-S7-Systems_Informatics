// #############################################################################
// # File logic.c
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>   // pid_t , uid_t , gid_t
#include <sys/utsname.h> // struct utsname

#include "logic.h"
#include "ui.h"
#include "macros.h"
#include "commands.h"

/* Reads a line in a standard mode */
char *read_line_v1()
{
    char *buffer = NULL;
    char c;
    int index = 0;
    int buffer_size = MAX_LINE_LENGTH;

    // Allocating memory for the line
    buffer = malloc(sizeof(char) * buffer_size);

    // Treat error if memory allocation fails
    if (buffer == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for buffer used at read_line_v1.\n");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        c = getchar();
        if (c == '\n' || c == EOF)
        {
            buffer[index] = '\0';
            break; // conditon to exit th einfinite loop is to dected the end_of_line or the cnhage of line via \n
        }
        else
        {
            buffer[index] = c;
            index++;
        }

        // // Checking if the buffer is full and trreating the error
        // if (index >= MAX_LINE_LENGTH - 1)
        // {
        //     fprintf(stderr, "Error: The input line is too long.\n");
        //     exit(EXIT_FAILURE);
        // }

        // Reallocating memory if the buffer is full
        if (index >= buffer_size)
        {
            buffer_size = buffer_size + MAX_LINE_LENGTH; // +MAX_LINE_LENGTH to to the existing buffer size
            buffer = realloc(buffer, sizeof(char) * buffer_size);
            if (buffer == NULL)
            {
                fprintf(stderr, "Error: Failed to reallocate memory for buffer that is used at read_line_v1.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return buffer;
}

/* Improuved version of the function read_line_v1 that uses the getline integrated function */
char *read_line_v2()
{
    char *buffer = NULL;
    size_t len = 0;

    if (getline(&buffer, &len, stdin) == -1)
    {
        if (feof(stdin))
        {
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        else
        {
            fprintf(stderr, "Error: Failed to read line using read_line_2 function.\n");
            free(buffer);
            exit(EXIT_FAILURE);
        }
    }

    return buffer;
}

/* It divides the line that was read in arguments */
char **parse_line(char *line, int *arg_count)
{
    // int arg_size = MAX_ARG_LENGTH;
    int index = 0;
    char *arg;
    // char **arguments = malloc(arg_size * sizeof(char *)); // an array of strings to hold the arguments

    // creating an array of strings to hold the arguments
    char **arguments = NULL;
    int size = MAX_ARGS;
    arguments = (char **)malloc(size * sizeof(char *));

    // Treat error if memory allocation fails
    if (arguments == NULL)
    {
        fprintf(stderr, "arguments table allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocating memory for each argument in the array
    for (int i = 0; i < size; i++)
    {
        arguments[i] = (char *)malloc(MAX_ARG_LENGTH * sizeof(char));
        if (arguments[i] == NULL)
        {
            fprintf(stderr, "arguments table allocation failed at number %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // Start of th eprocess to parse the line into arguments
    arg = strtok(line, DELIMITERS); // taking the first argument

    while (arg != NULL)
    {
        arguments[index] = arg;
        index++;
        *arg_count = index; // updating the number of arguments found in the line

        if (index >= size)
        {
            size = size + MAX_ARGS;
            arguments = (char **)realloc(arguments, size * sizeof(char *));

            // Reallocating memory for each argument in the array after geneal reallocation
            for (int i = index; i < size; i++)
            {
                arguments[i] = (char *)malloc(MAX_ARG_LENGTH * sizeof(char));
                if (arguments[i] == NULL)
                {
                    fprintf(stderr, "arguments table allocation failed at number %d\n", i + 1);
                    exit(EXIT_FAILURE);
                }
            }

            // Treat error if memory reallocation failed
            if (arguments == NULL)
            {
                fprintf(stderr, "arguments table reallocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        arg = strtok(NULL, DELIMITERS);
    }

    arguments[index] = NULL; // Null in order to declare the termination of the array of arguments

    return arguments;
}

/* Forks a process, and saves the return value for a command that comes with a list of arguments */
int command_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) // Child process
    {
        if (execvp(args[0], args) == -1) // Command execution is happening right here
        {
            perror("Error: Failed to execute the command.");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) // We are in error case
    {
        perror("Error: Failed to fork the process. Check command_launch function.");
    }
    else // The parent needs to wait for the command to finish running
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // Wait until either the processes are exited or killed. (EXIT or SIGNALED) <==> (!EXITT and !SIGNALED)
    }

    return 1;
}

/* Builtin commands and system commands logic combined all together to an execution script that updates teh status of the main flag */
int execute(char **args)
{
    int i;
    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }

    // Builtin commands
    for (i = 0; i < NUM_BUILTINS; i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return command_launch(args);
}

/* Main logic and structure of the shell */
void loop()
{
    // Variables initailisation
    char *line;
    char **arguments;
    int arg_count = 0;
    int status = 0;

    // Retrieving user name if available
    char *username = getenv("USER");
    if (username == NULL)
    {
        username = getenv("LOGNAME"); // if "USER" is not set
    }

    // Retrieving the hostname of the computer
    char hostname[MAX_DEFAULT]; // Buffer to store the hostname
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        perror("Error retrieving hostname");
        exit(EXIT_FAILURE);
    }

    cyan();
    printf("================ START ==============\n");
    reset();

    // Printing the date and time
    printf("Starting session at: ");
    print_time();
    printf("\n");

    // Sheel loop starts here
    do
    {
        if (username != NULL)
        {
            // printf("\n%s@macbookpro %% ", username);
            printf("%s@%s %% ", username, hostname);
            line = read_line_v2();
            arguments = parse_line(line, &arg_count);
            // for (int i = 0; i < arg_count; i++)
            // {
            //     printf("Argument %d: %s\n", i + 1, arguments[i]);
            // }

            // command_launch(arguments);
            status = execute(arguments);

            // Freeing memory allocated for the line and arguments and repeat the process if authorised to do so
            free(line);
            free(arguments);
        }
        else
        {
            printf("Unable to retrieve the username.\n");
            exit(EXIT_FAILURE);
        }

    } while (status);

    printf("\nEnding session at: ");
    print_time();

    cyan();
    printf("\n================= END ===============\n");
    reset();
}
