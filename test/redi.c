#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void		check_redi(char **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (!(strcmp(" ", cmd[i])))
			continue ;
		else if (!(strcmp(">", cmd[i])))
			printf("Aqui viene >\n");
		else if (!(strcmp(">>", cmd[i])))
			printf("Aqui viene >>\n");
		else if (!(strcmp("<<", cmd[i])))
			printf("Aqui viene <<\n");
	}
}


int		main(void)
{
	char **cmd;
	char *pwd;

	cmd = malloc(sizeof(char*) * 6);
	cmd[0] = "pwd";
	cmd[1] = " ";
	cmd[2] = ">>";
	cmd[3] = " ";
	cmd[4] = "texto.txt";
	cmd[5] = NULL;

	for (int i = 0; cmd[i] != NULL ; i++)
		printf("tab[%d] = [%s]\n", i, cmd[i]);
	pwd = getcwd(NULL, 0);
	printf("pwd -> [%s]\n", pwd);
	check_redi(cmd);
	return (0);
}
