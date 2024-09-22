#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void forkexample()
{
    pid_t p;
    p = fork();
    if (p < 0)
    {
        perror("fork fail");
        exit(1);
    }
    // child process because return value zero
    else if (p == 0)
        for (int i = 0; i < 5; i++)
        {
            printf("Child : %d\n", i);
        }

    // parent process because return value non-zero.
    else
        for (int i = 0; i < 5; i++)
        {
            printf("Parent : %d\n", i);
        }
}
// Not guarateed that parent is executed before child
int main()
{
    forkexample();
    return 0;
}