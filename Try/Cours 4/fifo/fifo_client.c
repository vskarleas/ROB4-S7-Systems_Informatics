// use FIFO (not pipes) to implement a simple client-server model
// the client
#include "fifocs.h"

int main(int argc, char **argv)
{
    int readfd, writefd;
    
    // open the fifos: assume the server already created them
       
    if ( (writefd = open(FIFO1, 1)) < 0)
      { printf("client: can't open FIFO1 to write\n"); return 1; }
    if ( (readfd = open(FIFO2, 0)) < 0)
      { printf("client: can't open FIFO2 to read\n"); return 1; }
    
    /* client(readfd, writefd); */
      
    close(readfd);
    close(writefd);

    // now delete the fifos since we're finished
    
    if (unlink(FIFO1) < 0)
      { printf("client: can't unlink FIFO1"); return 1; }
    if (unlink(FIFO2) < 0)
      { printf("client: can't unlink FIFO2"); return 1; }

    return 0;
}
    
