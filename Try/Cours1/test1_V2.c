/* a test using define */
#define DMSG "Hello students !"
#include <stdio.h>
int main(int argc, char *argv[])
{
    const char msg[] = DMSG;
    puts(msg);
    return 0;
}