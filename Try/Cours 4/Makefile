GCC_FLAGS = -Wall -g

all: pipe1 pipe2

pipe2 : pipefork2.o
	gcc $(GCC_FLAGS) -o pipe2 pipefork2.o

pipe1 : pipefork.o
	gcc $(GCC_FLAGS) -o pipe1 pipefork.o

pipefork2.o : pipefork2.c
	gcc $(GCC_FLAGS) -c pipefork2.c

pipefork.o : pipefork.c
	gcc $(GCC_FLAGS) -c pipefork.c

clean :
	rm -f *.o pipe1 pipe2
