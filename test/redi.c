#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


void		intentofork(char **av, char **envp)
{
	pid_t	f;
	char	*pwd = getcwd(NULL, 0);
	int		fd;
	char	*path = "tontolonero";

	if ((fd = open(path, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR
                     | S_IRGRP | S_IROTH)) == -1)
	{
		printf("minishell: %s: %s\n", strerror(errno), path);
		return ;
	}
	if ((f = fork()) == 0)
	{
		dup2(fd, 1);
		execve("/bin/ls",av, envp);
		exit(1);
	}
//	printf("%s\n", pwd);
	close(fd);
}
void		intento(char **av, char **envp)
{
	char	*pwd = getcwd(NULL, 0);
	int		fd;
	char	*path = "tontolonero";

	if ((fd = open(path, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR
                     | S_IRGRP | S_IROTH)) == -1)
	{
		printf("minishell: %s: %s\n", strerror(errno), path);
		return ;
	}
	dup2(fd, 1);
	execve("/bin/ls",av, envp);
//	printf("%s\n", pwd);
	close(fd);
}

void		intento2()
{
	char	*pwd = getcwd(NULL, 0);
	int		fd;
	char	*path = "toto.txt";

	if ((fd = open(path, O_APPEND | O_WRONLY | O_CREAT , 0644)) == -1)
	{
		printf("minishell: %s: %s\n", strerror(errno), path);
		return ;
	}
	dup2(fd, 1);
	printf("%s", pwd);
	close(fd);
}

int			is_redi(char *str)
{
	return (!(strcmp(">", str)) || !(strcmp(">>", str))
			|| !(strcmp("<", str)));
}

void		check_redi(char **cmd, char **av, char **envp)
{
	int		i;
	char	*n_forlder;
	int		size_tab;

	i = -1;
	while (cmd[++i])
	{
		if (is_redi(cmd[i]))
		{
			if (cmd[++i])
			{
				if (!(cmd[i + 1]) || is_redi(cmd[i + 1]))
				{
					printf("minishell: syntax error near unexpected token `%s'\n", cmd[i - 1]);
					return ;
				}
			}
			else
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return ;
			}
		}
	}
	i = -1;
	while (cmd[++i])
	{
		if (!(strcmp(" ", cmd[i])))
			continue ;
		else if (!(strcmp(">", cmd[i])))
		{
			intentofork(av, envp);
		}
		else if (!(strcmp(">>", cmd[i])))
		{
			intento2();
		}
		else if (!(strcmp("<<", cmd[i])))
			printf("Aqui viene <<\n");
	}

}


int			main(int ac, char **av, char **envp)
{
	char **cmd;

	cmd = malloc(sizeof(char*) * 10);
	cmd[0] = "pwd";
	cmd[1] = " ";
	cmd[2] = ">>";
	cmd[3] = " ";
	cmd[4] = "nanita";
	cmd[5] = " ";
	cmd[6] = ">";
	cmd[7] = " ";
	cmd[8] = "nanita";
	cmd[9] = NULL;

	for (int i = 0; cmd[i] != NULL ; i++)
		printf("tab[%d] = [%s]\n", i, cmd[i]);
	check_redi(cmd, av, envp);
	(void)ac;
	return (0);
}
