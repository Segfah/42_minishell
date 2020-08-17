/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/04 04:01:55 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     command_bin(char **tab)
{
	char *new_env[] = {NULL};
	char *command;
	int i;
	pid_t f;
	pid_t w;
	int	 status;

	f = fork();
	i = 0;
	if (!(command = (char*)malloc(sizeof(char) * ft_strlen(tab[0]) + 6)))
		return(0);
	command[0] = '/';
	command[1] = 'b';
	command[2] = 'i';
	command[3] = 'n';
	command[4] = '/';
	while (tab[0][i] != '\0')
	{
		command[i + 5] = tab[0][i];
		i++;
	}
	command[i + 5] = '\0';
	//printf("command = [%s]\n", command);
	/*	int a;
		a = 0;
		while (tab[a] != NULL)
		{
		printf("tab[%d] = {%s}\n", a , tab[a]);
		a++;
		}
		} */
	if (f == 0)
	{
		if (execve(command, tab, new_env) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		/*
		** Sorry pour changer un peu ta fonction, j'avais besoin de prendre...
		** ...le return du fils pour pouvoir bien le fermer.
		*/
		if ((w = waitpid(f, &status, WUNTRACED | WCONTINUED)) == -1)
			exit(1);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 1)
			{
				free(command);
				return (-1);
			}
	}
	free(command);
	return (0);
}