#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>
#include <time.h>

extern int errno;

#define FIFO1 "/tmp/my_fifo1"
#define FIFO2 "/tmp/my_fifo2"

#define PERMISSIONS 0666


