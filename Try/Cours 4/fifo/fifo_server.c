// use FIFO (not pipes) to implement a simple client-server model
// the server
#include "fifocs.h"

int main(int argc, char **argv)
{
    int readfd, writefd;
    
    if( (mkfifo(FIFO1,PERMISSIONS)<0) && (errno != EEXIST) )
    {
        printf("server: can't create FIFO1 to read: %s \n", FIFO1); return 1;
    }
    
    if( (mkfifo(FIFO2,PERMISSIONS)<0) && (errno != EEXIST) )
    {
        unlink(FIFO1);
        printf("server: can't create FIFO2 to write: %s \n", FIFO2); return 1;
    }
    
    if ( (readfd = open(FIFO1, 0)) < 0)
        { printf("server: can't open FIFO1 to read \n"); return 1; }
    if ( (writefd = open(FIFO2, 1)) < 0)
        { printf("server: can't open FIFO2 to write \n"); return 1; }
  
    /* server(readfd, writefd); */
    
    // just to give the time to the client to test the fifos
    sleep(1000);
             
    close(readfd);
    close(writefd);     
    return 0;
}
