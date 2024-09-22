#include <unistd.h>    // getpid () , gettpid () , getuid () , getgid ()
#include <sys/types.h> // pid_t , uid_t , gid_t
#include <stdio.h>     // fprintf ()


    int
    main(int argc, char **argv)
{
    // Récupérer les informations sur le processus courant
    pid_t my_pid = getpid();
    pid_t my_ppid = getppid();
    uid_t my_uid = getuid();
    gid_t my_gid = getgid();
    fprintf(stdout, "Attributs␣de␣ce␣processus␣:\n");
    fprintf(stdout, "Mon pid vaut : %d\n", my_pid);
    fprintf(stdout, "Mon ppid vaut : %d\n", my_ppid);
    fprintf(stdout, "Mon uid vaut : %d\n", my_uid);
    fprintf(stdout, "Mon gid vaut : %d\n", my_gid);
}