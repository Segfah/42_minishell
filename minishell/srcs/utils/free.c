/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:58:38 by lryst             #+#    #+#             */
/*   Updated: 2020/09/10 18:50:41 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*ft_strcatdup(char *s1, char *s2)
{
	char *ret;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return NULL;
	while (s1[i++])
		ret[i] = s1[i];
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	ft_free(s1);
	ft_free(s2);
	return (ret);
}

void				ft_free(char *str)
{
	free(str);
	str = NULL;
}

void				ft_free_double_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void				free_node_cmd(l_cmd *node)
{
	(node->input != NULL) ? free(node->input) : 0;
	node->input = NULL;
	(node->output != NULL) ? free(node->output) : 0;
	node->output = NULL;
	printf("free node\n");
	free(node);
	node = NULL;
}

void				free_cmd(l_cmd *cmd)
{
	l_cmd		*tmp;

	while (cmd != NULL)
	{
		write(1, "free cmd\n", 9);
		tmp = cmd->next;
		free_node_cmd(cmd);
		cmd = tmp;
	}
	free(cmd);
}