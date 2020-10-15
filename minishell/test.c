#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

int	main(int ac, char **av)
{
	char **tab_env;
	int j;

	j = execve(av[1], av, tab_env);

	printf("%d <-> %s\n", j ,strerror(errno));
	return (0);
}
