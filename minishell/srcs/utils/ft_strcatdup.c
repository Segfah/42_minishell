/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:00:14 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 10:07:03 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*ft_strcatdup(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(ret = (char*)malloc(sizeof(char) * (i + j) + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	ft_free(s1);
	ft_free(s2);
	return (ret);
}

int					strcat_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->next && tmp->next->output &&
		check_before_cat_node(tmp->input, tmp->next->input))
		{
			if ((tmp->input = ft_strcatdup(tmp->input, tmp->next->input)))
				tmp->next->input = NULL;
			if ((tmp->output = ft_strcatdup(tmp->output, tmp->next->output)))
				tmp->next->output = NULL;
			i = 1;
			break ;
		}
		tmp = tmp->next;
	}
	remove_null_node(cmd);
	return (i);
}
