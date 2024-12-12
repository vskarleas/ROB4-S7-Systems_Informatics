#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv)
{
  int fd[2];  


  if (pipe(fd))                           /* create pipe            */
    fprintf(stderr, "pipe error\n");
  else if (fork()) 
  {                       		            /* parent: the reader  */
      int reception;
      close(fd[1]);                       /* close the write pipe */
      read(fd[0], &reception, sizeof (int));      /* read an integer        */
      printf("Parent: reading the value %d\n", reception);
  } 
  else 
  {
        int envoi;                            		      /* child: the writer      */
      close(fd[0]);
      srand(time(NULL));                  
      envoi = rand();                         /* generates integer */
      printf("Child: writing the value %d\n", envoi);
      write(fd[1], &envoi, sizeof (int));     /* writes the integer */
   }

  return 0;
}
