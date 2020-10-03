/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:27:31 by lryst             #+#    #+#             */
/*   Updated: 2020/10/03 23:12:14 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_option_echo(char *arg)
{
	int i;
	int len;

	len = ft_strlen(arg);
	i = 0;
	if (arg[i] == '-' && arg[i + 1] == 'n')
	{
		while
	}
}

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

void    gestion_echo(t_cmd *cmd)
{
	t_cmd *test;
	int n;

	test = cmd;
	n = 0;
	if (test->next != NULL)
		test = test->next;
	else
		n = 1;
	if (test->next != NULL)
		test = test->next;
	if (ft_strcmp(test->output, "-n") == 0)
	{
		test = test->next;
		if (test != NULL)
			test = test->next;
		n = 2;
	}
	if (n == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	while (test)
	{
		ft_printf("%s", test->output);
		test = test->next;
	}
	//ft_free_double_tab(tab);
	g_ret = 0;
	if (n == 0)
		ft_printf("\n");
}
