/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:27:31 by lryst             #+#    #+#             */
/*   Updated: 2020/11/25 18:49:23 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			no_file_or_dir(char *tabcmd, t_lists *var)
{
	int		i;
	int		save;
	int		size;
	char	*tmp;
	t_lists	*revar;

	i = 0;
	revar = var;
	while (tabcmd[i])
	{
		if (tabcmd[i] == '$')
		{
			i++;
			save = i;
			while (tabcmd[i] && ((tabcmd[i] > 47 && tabcmd[i] < 58) ||
			(tabcmd[i] > 64 && tabcmd[i] < 91) || (tabcmd[i] > 96 &&
			tabcmd[i] < 123)))
				i++;
			if (!(tmp = (char*)malloc(sizeof(char) * (i - save) + 1)))
				return (-1);
			size = 0;
			while (save < i)
				tmp[size++] = tabcmd[save++];
			tmp[size] = '\0';
			revar = var;
			while (revar)
			{
				if (!revar->name && !revar->data)
					break ;
				if (ft_strcmp(revar->name, tmp) == 0)
				{
					ft_free(tmp);
					return (1);
				}
				revar = revar->next;
			}
			i--;
			ft_free(tmp);
		}
		if (tabcmd[i])
			i++;
	}
	return (0);
}

void		cmd_not_found(char *tabcmd, t_temp *tmp)
{
	//printf("tabcmd =[%s]\n", tabcmd);
	//printftab(tmp->strcmdin);
	g_ret = 127;
	write(2, "minishell: ", 11);
	write(2, tmp->strcmd[0], ft_strlen(tmp->strcmd[0]));
	if (no_file_or_dir(tmp->strcmdin[0], tmp->varenv) == 1)
		write(2, ": No such file or directory\n", 28);
	else
		write(2, ": command not found\n", 20);
	(void)*tabcmd;
}

void		gestion_echo_2(t_temp *tmp, int n, int i)
{
	while (tmp->strcmd[i])
	{
		ft_printf("%s", tmp->strcmd[i]);
		i++;
	}
	g_ret = 0;
	if (n == 0)
		ft_printf("\n");
}

void		gestion_echo(t_temp *tmp)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	dup_or_not(tmp);
	if (echo_cote_space(tmp) == 0)
	{
		(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
		return ;
	}
	i = 2;
	if (!check_multi_options(tmp, &i, &n))
		return ;
	gestion_echo_2(tmp, n, i);
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
}

int			check_echo_2(int *check, int *i, char c, char *s)
{
	if (s && s[*i] && (s[*i] == c || s[*i] == c - 40))
	{
		*check += 1;
		(*i)++;
		return (*check);
	}
	*check = 0;
	return (0);
}
