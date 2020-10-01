#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);

int main ()
{
	signal(SIGINT, sighandler);

	pid_t f;
	char* argv[] = { "cat", NULL };
	char* envp[] = { "some", "environment", NULL };

	if ((f = fork()) == 0)
	{
		execve("/bin/cat", argv, envp);
	}
	return(0);
}

void sighandler(int signum)
{
	printf("Caught signal %d, coming out...\n", signum);
	exit(1);
}
