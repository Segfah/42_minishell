/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:54:35 by lryst             #+#    #+#             */
/*   Updated: 2020/08/11 20:19:11 by lryst            ###   ########.fr       */
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
		ft_strcmp(arg, "-n") == 0 ? i = 8 : 0;
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

void    gestion_echo(char *str, char *arg, t_temp *temp)
{
	char *cmd;
	char **tab;
	int i;

	i = -1;
	if (ft_strcmp(str, "echo") != 0)
	{
		if (!(cmd = gestion_echo_option(str, arg)))
			return ;
		if (!(tab = ft_split_echo(cmd, temp)))
			return ;
		ft_free(cmd);
		while (tab[++i] != NULL)
			ft_printf("%s", tab[i]);
		ft_free_double_tab(tab);
	}
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(arg, "-n") != 0)
		ft_printf("\n");
}



/* void	gestion_echo(char *str, char *arg)
{
	//char *cmd;
	//char **tab;
	int i;

	i = 4;
	if (ft_strcmp(str, "echo") != 0)
	{
		ft_strcmp(arg, "-n") == 0 ? i = 8 : 0;
		printf("i = %d\n", i);
		
		ft_printf("str = [%s]\n", str);
	}
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(arg, "-n") != 0)
		ft_printf("\n");
} */ 