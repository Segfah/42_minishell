/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:00:46 by corozco           #+#    #+#             */
/*   Updated: 2020/11/22 18:48:29 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			sighandler(int signum)
{
	char		*prompt;
	char		*env;

	write(1, "\b\b  \n", 5);
	env = getcwd(NULL, 0);
	if ((prompt = ft_prompt(env)) == NULL)
		exit(1);
	ft_printf("\x1b[33m%s\x1b[0m🐰: ", prompt);
	ft_free(env);
	env = NULL;
	ft_free(prompt);
	prompt = NULL;
	(void)signum;
}

void			sighandler2(int signum)
{
	(void)signum;
	write(1, " \b\b \b\b \b", 8);
}
