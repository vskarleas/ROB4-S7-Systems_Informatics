/* Alexandre Coninx
 * ISIR CNRS/UPMC
 * 07/10/2015 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int desc[2];

	char *ls_args[] = {"ls", "-l", NULL};
	char *wc_args[] = {"wc", "-l", NULL};
	
	int pid;
	if(pipe(desc))
	{
		perror("Pipe creation failed");
		return(1);
	}
	
	pid = fork();
	if (pid == 0)
	{
		//L'enfant s'occupe du wc -l
		
		//On ferme le pipe en écriture
		close(desc[1]);
		
		//On remplace l'entrée standard avec la lecture sur le pipe
		dup2(desc[0], STDIN_FILENO);
		
		//On execute wc -l
		
		execvp("wc", wc_args);
	}
	else
	{
		// Le parent s'occupe du ls -l
		//On ferme le pipe en lecture
		close(desc[0]);
		
		//On remplace la sortie standard avec l'écriture sur le pipe
		dup2(desc[1], STDOUT_FILENO);
		//On exécute ls -l
		execvp("ls", ls_args);
	}
}

