/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 02:32:22 by corozco           #+#    #+#             */
/*   Updated: 2020/08/20 02:01:32 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Elle tri la liste export
*/

void		range_export(t_lists *la)
{
	t_lists	*tmp;
	t_lists	*tmp1;
	t_lists	*tmp3;
	char	*s1;
	char	*s2;

	tmp = la;
	while (tmp->next != NULL)
	{
		tmp3 = tmp;
		tmp1 = tmp->next;
		while (tmp1 != NULL)
		{
			if (ft_strcmp(tmp1->name, tmp3->name) < 0)
				tmp3 = tmp1;
			tmp1 = tmp1->next;
		}
		s1 = tmp->name;
		s2 = tmp->data;
		tmp->name = tmp3->name;
		tmp->data = tmp3->data;
		tmp3->name = s1;
		tmp3->data = s2;
		tmp = tmp->next;
	}
}

char			*str_key(char *str)
{
	char		*ss;
	char		*tmp;

	tmp = ft_strchr(str, '=');
	if (tmp != NULL)
	{
		str[tmp - str] = 0;
		if (!(ss = ft_strdup(str)))
			return (NULL);
		str[(int)ft_strlen(str)] = '=';
	}
	else
	{
		if (!(ss = ft_strdup(str)))
			return (NULL);
	}
	return (ss);
}

int			search_list(t_lists *head, char *ss)
{
	t_lists		*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, ss) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int				done_list(t_lists *head, char *ss, char **data)
{
	t_lists		*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, ss) == 0)
			if ((*data = ft_strdup(tmp->data)) == NULL)
				return (-1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** key (1) == la commande que j'utilise pour modifier mes env
** key != (1) pour chercher un node et returner une string malloquee
** example
**			test
**			char *data;
**			data = NULL;
**			search_env("HOME", tmp, 0, &data);
**			ft_printf("data = [%s]\n", data);
**			free(data); //tu free apres l'utilisation de la data.
*/

int				search_env(char *str, t_temp *tmp, int key, char **data)
{
	char		*ss;
	int			ret;

	ret = 0;
	if ((ss = str_key(str)) == NULL)
		return (-1);
	if (key == 1)
		ret = search_list(tmp->varenv, ss);
	else
	{
		if ((ret = done_list(tmp->varenv, ss, data)) == -1)
		{
			free(ss);
			return (-1);
		}
	}
	free(ss);
	return (ret);
}

int				check_env(char *str, int key)
{
	int			i;

	if (key == 1)
	{
		if ((ft_isalpha(str[0]) == 0) && str[0] != '_')
			return (-1);
		i = 1;
	}
	else
		i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (-1);
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

int				lback(t_lists **alst, char *str, char *str2)
{
	t_lists		*tmp;
	t_lists		*new;

	if (!(new = ft_memalloc(sizeof(t_lists))))
		return (-1);
	if (!(new->name = ft_strdup(str)))
		return (-1);
	if (str2)
	{
		if (!(new->data = ft_strdup(str2)))
			return (-1);
	}
	else
		new->data = NULL;
	new->next = NULL;
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (0);
}

int				ft_cortar(char *tab[2], char *str)
{
	int			i;
	char		*ss;

	if ((i = check_env(str, 1)) == -1)
		return (-2);
	else if (i == 0)
	{
		if (!(tab[0] = ft_strdup(str)))
			return (-1);
		tab[1] = NULL;
	}
	else
	{
		ss = ft_strchr(str, '=');
		if (!(tab[1] = ft_strdup(ss + 1)))
			return (-1);
		str[ss - str] = 0;
		if (!(tab[0] = ft_strdup(str)))
			return (-1);
		str[(int)ft_strlen(str)] = '=';
	}
	return (0);
}

void			gestion_export(t_temp *tmp)
{
	int			i;
	int			ret;
	char		*tab[2];

	i = 0;
	ret = 0;
	while (tmp->strcmd[i])
		i++;
	if (i == 1)
	{
		cpy_env(&tmp->exportenv, tmp->varenv);
		range_export(tmp->exportenv);
		print_list(tmp->exportenv, 0);
		free_list(tmp->exportenv);
	}
	else
	{
		i = 0;
		while (tmp->strcmd[++i])
		{
			if ((ret = ft_cortar(tab, tmp->strcmd[i])) == -2)
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n",
						tmp->strcmd[i]);
				break ;
			}
			else if (ret == -1)
			{
				ft_printf("error malloc\n"); // a cambiar.la foncion a int gest.
				exit(1);
			}
			else
			{
				if ((ret = search_env(tab[0], tmp, 1, NULL)) == 0)
				{
					if ((lback(&tmp->varenv, tab[0], tab[1])) == -1)
						exit(1);
				}
				else if (ret == 1 && tab[1] != NULL)
					ft_printf("usar el unset + el addback para hacer esto\n");
			}
			free(tab[0]);
			if (tab[1] != NULL)
				free(tab[1]);
		}
	}
}
