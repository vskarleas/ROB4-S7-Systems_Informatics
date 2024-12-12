GCC_FLAGS = -Wall -g

all: fifo_client fifo_server fifo_client2 fifo_server2

fifo_client : 
	gcc $(GCC_FLAGS) fifo_client.c fifocs.h -o fifo_client
	
fifo_client2 : 
	gcc $(GCC_FLAGS) fifo_client2.c fifocs.h -o fifo_client2
	
fifo_server : 
	gcc $(GCC_FLAGS) fifo_server.c fifocs.h -o fifo_server
	
fifo_server2 : 
	gcc $(GCC_FLAGS) fifo_server2.c fifocs.h -o fifo_server2

clean :
	rm -f *.o fifo_client fifo_server fifo_client2 fifo_server2
	

