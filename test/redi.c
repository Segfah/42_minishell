#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void		intento(char **av, char **envp)
{
	char	*pwd = getcwd(NULL, 0);
	int		fd;

	if ((fd = open("nani.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR
                     | S_IRGRP | S_IROTH)) == -1)
		return ;
	dup2(fd, 1);
	execve("/bin/ls",av, envp);
//	printf("%s\n", pwd);
}

void		intento2()
{
	char	*pwd = getcwd(NULL, 0);
	int		fd;

	if ((fd = open("toto.txt", O_RDWR| O_CREAT, S_IRUSR | S_IWUSR
                     | S_IRGRP | S_IROTH)) == -1)
		return ;
	dup2(fd, 1);
	printf("%s\n", pwd);
}

void		check_redi(char **cmd, char **av, char **envp)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (!(strcmp(" ", cmd[i])))
			continue ;
		else if (!(strcmp(">", cmd[i])))
			intento(av, envp);
		else if (!(strcmp(">>", cmd[i])))
			intento2();
		else if (!(strcmp("<<", cmd[i])))
			printf("Aqui viene <<\n");
	}
}


int			main(int ac, char **av, char **envp)
{
	char **cmd;

	cmd = malloc(sizeof(char*) * 6);
	cmd[0] = "pwd";
	cmd[1] = " ";
	cmd[2] = ">";
	cmd[3] = " ";
	cmd[4] = "texto.txt";
	cmd[5] = NULL;

	for (int i = 0; cmd[i] != NULL ; i++)
		printf("tab[%d] = [%s]\n", i, cmd[i]);
	check_redi(cmd, av, envp);
	(void)ac;
	return (0);
}
