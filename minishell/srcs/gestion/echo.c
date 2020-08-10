/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:54:35 by lryst             #+#    #+#             */
/*   Updated: 2020/08/10 19:23:24 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*gestion_echo_option(char *str, char *arg)
{
	char *cmd;
	int i;
	int j;
	int save;

	i = 4;
	j = 0;
	if (ft_strcmp(arg, "-n") == 0)
	{
		(str[i] == '-' && str[i + 1] == 'n') ? i = i + 2 : 0;
	}
	save = i;
	while (str[i++] != '\0')
		j++;
	if (!(cmd = (char*)malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = save;
	j = 0;
	while (str[i] != '\0') 
		cmd[j++] = str[i++];
	cmd[j] = '\0';
	return (cmd);
}

void    gestion_echo(char *str, char *arg)
{
	char *cmd;
	char **tab;
	int i;

	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "echo -n") == 0)
		return ;
	if (!(cmd = gestion_echo_option(str, arg)))
		return ;
	if (!(tab = ft_split_echo(cmd, ' ')))
		return ;
	ft_free(cmd);
	i = -1;
	while (tab[++i] != NULL)
		ft_printf("%s", tab[i]);
	if (ft_strcmp(arg, "-n") != 0)
		ft_printf("\n");
	ft_free_double_tab(tab);
}