/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:27:31 by lryst             #+#    #+#             */
/*   Updated: 2020/10/04 18:54:07 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_option_echo(char *s)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '-')
	{
		if (s[i + 1])
			i++;
		while (s[i] && s[i] == 'n')
			i++;
	}
	printf("len = %d | i = %d | total = %d\n", len, i, len - 1);
	if (i == len)
		return (i);
	return (0);
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
	if (ft_check_option_echo(test->output) != 0)
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
