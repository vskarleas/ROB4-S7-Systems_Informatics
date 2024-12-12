// use FIFO (not pipes) to implement a simple client-server model
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>
#include <time.h>

extern int errno;

#define FIFO1 "/tmp/fifo1.txt"
#define FIFO2 "/tmp/fifo2.txt"

#define PERMISSIONS 0666

int main(int argc, char **argv)
{
    int childpid, readfd, writefd;
    
    if( (mkfifo(FIFO1,PERMISSIONS)<0) && (errno != EEXIST) )
    {
        printf("Cannot create fifo 1: %s \n", FIFO1);
        return 1;
    }
    
    if( (mkfifo(FIFO2,PERMISSIONS)<0) && (errno != EEXIST) )
    {
        unlink(FIFO1);
        printf("Cannot create fifo 2: %s \n", FIFO1);
        return 1;
    }
    
    childpid = fork();
    
    if(childpid > 0)
    {
        // parent
        if ( (writefd = open(FIFO1, 1)) < 0)
            err_sys("parent: can't open write fifo");
        if ( (readfd = open(FIFO2, 0)) < 0)
            err_sys("parent: can't open read fifo");
        
        client(readfd, writefd);
        
        while (wait((int *) 0) != childpid) /* wait for child */
        ;
        
        close(readfd);
        close(writefd);

        if (unlink(FIFO1) < 0)
        err_sys("parent: can't unlink %s", FIFO1);
        if (unlink(FIFO2) < 0)
        err_sys("parent: can't unlink %s", FIFO2);
    
        return 0;
    }
    else
    {
        // child
        
        if ( (readfd = open(FIFO1, 0)) < 0)
            err_sys("child: can't open read fifo");
        if ( (writefd = open(FIFO2, 1)) < 0)
            err_sys("child: can't open write fifo");
        server(readfd, writefd);
        
        close(readfd);
        close(writefd);
        
        return 0;
    
    }
    


  int fd[2];  
  int i;

  if (pipe(fd))                         /* create pipe            */
    fprintf(stderr, "pipe error\n");
  else if (fork()) 
  {                       		/* parent will be reader  */
      close(fd[1]);                     /* close the `write' pipe */
      read(fd[0], &i, sizeof (int));    /* read an integer        */
      printf("Read the value %d\n", i);
  } 
  else 
  {                            		/* child: the writer      */
      close(fd[0]);
      srand(time(NULL));
      i = rand();
      printf("Writing the value %d\n", i);
      write(fd[1], &i, sizeof (int));
   }

  return 0;
}
