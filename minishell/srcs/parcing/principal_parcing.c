/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 02:30:51 by corozco           #+#    #+#             */
/*   Updated: 2020/09/02 20:45:17 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** fonction qui va creer le nouveau tableau a partir de tabcmd (strig)
*/

void	double_cote_cmd(l_cmd *cmd, t_lists *var)
{
	int i;
	int j;
	int size;
	int save;
	char *tmp;
	int len;
	t_lists	*revar;

	i = 1;
	j = 0;
	size = 0;
	revar = var;
	len = ft_strlen(cmd->input) - 1;
	while (cmd->input[i] && i < len)
	{
		if (cmd->input[i] == '$')
		{
			if (cmd->input[i] && ((cmd->input[i + 1] > 47 && cmd->input[i + 1] < 58) || (cmd->input[i + 1] > 64 && cmd->input[i + 1] < 91) || (cmd->input[i + 1] > 96 && cmd->input[i + 1] < 123)))
			{
				i++;
				save = i;
				printf("save = %d, i = %d", save, i);
				while (cmd->input[i] && ((cmd->input[i] > 47 && cmd->input[i] < 58) || (cmd->input[i] > 64 && cmd->input[i] < 91) || (cmd->input[i] > 96 && cmd->input[i] < 123)))
					i++;
				if (!(tmp = (char*)malloc(sizeof(char) * (i - save) + 1)))
					return ;
				printf("save = %d, i = %d", save, i);
				while (save < i)
					tmp[j++] = cmd->input[save++];
				tmp[j] = '\0';
				printf("	tmp = [%s]\n", tmp);
				while (var)
				{
					if (ft_strcmp(var->name, tmp) == 0)
						size = size + ft_strlen(var->data);
					var = var->next;
				}
				ft_free(tmp);
			}
			else
				size++;
			i++;
		}
		if (cmd->input[i] == '\\')
		{
			save = 0;
			while (cmd->input[i] && cmd->input[i] == '\\')
			{
				save++;
				i++;
			}
			if (save == 1)
				size++;
			else
				size = size + (save / 2);
		}
		if (cmd->input[i] != '\\' && cmd->input[i] != '$')
			size++;
		i++;
	}
	if (!(cmd->output = (char*)malloc(sizeof(char) * size + 1)))
		return ;
	printf("size = %d\n", size);
	size = 0;
	i = 1;
	j = 0;
	while (cmd->input[i] && i < len)
	{
		if (cmd->input[i] == '$')
		{
			if (cmd->input[i] && ((cmd->input[i + 1] > 47 && cmd->input[i + 1] < 58) || (cmd->input[i + 1] > 64 && cmd->input[i + 1] < 91) || (cmd->input[i + 1] > 96 && cmd->input[i + 1] < 123)))
			{
				i++;
				save = i;
				while (cmd->input[i] && ((cmd->input[i] > 47 && cmd->input[i] < 58) || (cmd->input[i] > 64 && cmd->input[i] < 91) || (cmd->input[i] > 96 && cmd->input[i] < 123)))
					i++;
				if (!(tmp = (char*)malloc(sizeof(char) * (i - save) + 1)))
					return ;
				size = 0;
				while (save < i)
					tmp[size++] = cmd->input[save++];
				tmp[size] = '\0';
				printf("	tmp = [%s]\n", tmp);
				size = 0;
				while (revar)
				{
					printf("GOOOOO !\n");
					if (ft_strcmp(revar->name, tmp) == 0)
						while (revar->data[size])
							cmd->output[j++] = revar->data[size++];
					revar = revar->next;
				}
				printf("cmd->FAILED = [%s]\n", cmd->output);
				if (size == 0)
					i++;
			}
			else
				cmd->output[j++] = cmd->input[i];
			i++;
		}
		printf("	ICI\n");
		if (cmd->input[i] == '\\')
		{
			save = 0;
			size = 0;
			while (cmd->input[i] && cmd->input[i] == '\\')
			{
				save++;
				i++;
			}
			if (save == 1)
				cmd->output[j++] = cmd->input[i++];
			else
				while (size++ < (save / 2))
					cmd->output[j] = '\\';
		}
		if (cmd->input[i] != '\\' && cmd->input[i] != '$')
			cmd->output[j] = cmd->input[i];
		i++;
		j++;
	}
	cmd->output[j] = '\0';
}

void	single_cote_cmd(l_cmd *cmd)
{
	int i;
	int j;
	int len;

	i = 1;
	j = 0;
	len = ft_strlen(cmd->input);
	if (!(cmd->output = (char*)malloc(sizeof(char) * len)))
		return ;
	while (cmd->input[i] && i < (len - 1))
		cmd->output[j++] = cmd->input[i++];
	cmd->output[j] = '\0';
}

void	slash_cmd(l_cmd *cmd)
{
	int i;
	int count;

	i = 1;
	count = 0;
	if (cmd->input[i] != '\0' && cmd->input[i] != '\\')
	{
		if (!(cmd->output = (char*)malloc(sizeof(char) * ft_strlen(cmd->input))))
			return ;
		while (cmd->input[i])
			cmd->output[count++] = cmd->input[i++];
	}
	else
	{
		i = 0;
		while (cmd->input[i] && cmd->input[i++] == '\\')
			count++;
		if(!(cmd->output = (char*)malloc(sizeof(char) * (ft_strlen(cmd->input) / 2) + 1)))
			return;
		count = count / 2;
		i = 0;
		while (i < count)
			cmd->output[i++] = '\\';
	}
	cmd->output[i] = '\0';
}

void	replace_isspace(l_cmd *cmd, int *i, int *j, char ascii)
{
	cmd->output[*i] = ascii;
	(*i)++;
	*j = *j + 2;
}

void	dollar_cmd(l_cmd *cmd, t_lists *var)
{
	int i;
	int j;
	char *save;

	i = 1;
	j = 0;
	
	if (!(save = (char*)malloc(sizeof(char) * ft_strlen(cmd->input))))
		return ;
	while (cmd->input[i])
		save[j++] = cmd->input[i++];
	save[j] = '\0';
	j = 0;
	i = 0;
	if (save[j] == '\'')
	{
		j++;
		if ((cmd->output = (char*)malloc(sizeof(char) * ft_strlen(save))))
		{
			while (save[j] && save[j] != '\'')
			{
				if (save[j] == '\\' && save[j + 1] == 't')
					replace_isspace(cmd, &i, &j, '\t');
				else if (save[j] == '\\' && save[j + 1] == 'n')
					replace_isspace(cmd, &i, &j, '\n');
				else if (save[j] == '\\' && save[j + 1] == 'v')
					replace_isspace(cmd, &i, &j, '\v');
				else if (save[j] == '\\' && save[j + 1] == 'f')
					replace_isspace(cmd, &i, &j, '\f');
				else if (save[j] == '\\' && save[j + 1] == 'r')
					replace_isspace(cmd, &i, &j, '\r');
				else
					cmd->output[i++] = save[j++];
			}
		}
		return ;
	}
	if (ft_strcmp(cmd->input, "$\0") == 0)
	{
		cmd->output = ft_strdup(cmd->input);
		return ;
	}
	while (var)
	{
		if (ft_strcmp(var->name, save) == 0)
		{
			cmd->output = ft_strdup(var->data);
			ft_free(save);
			return ;
		}
		var = var->next;
	}
	cmd->output = NULL;
}

void	check_node(l_cmd *cmd, t_temp *temp)
{
	if (cmd->input[0] == '$')
		dollar_cmd(cmd, temp->varenv);
	if (cmd->input[0] == '\\')
		slash_cmd(cmd);
	if (cmd->input[0] == '\'')
		single_cote_cmd(cmd);
	if (cmd->input[0] == '"')
		double_cote_cmd(cmd, temp->varenv);
	else
		cmd->output = ft_strdup(cmd->input);
}

void	ft_lstadd_back_cmd(l_cmd **alst, l_cmd *new)
{
	l_cmd	*tmp;

	tmp = NULL;
	if (new)
	{
		if (!alst || !(*alst))
		{
			*alst = new;
			return ;
		}
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

l_cmd	*ft_lstnew_cmd(char *input, t_temp *temp)
{
	l_cmd	*tmp;

	if (!(tmp = malloc(sizeof(l_cmd))))
		return (NULL);
	if (input)
	{
		tmp->input = ft_strdup(input);
		check_node(tmp, temp);
	}
	else
		tmp->input = NULL;
	tmp->next = NULL;
	return (tmp);
}

void			separator_string(l_cmd **cmd, char *str, t_temp *tmp)
{
	int i;
	l_cmd *new;
	
	i = 0;
	tmp->strcmd = ft_split_strcmd(str, ' ');
	while(tmp->strcmd[i])
	{
		new = ft_lstnew_cmd(tmp->strcmd[i], tmp);
		ft_lstadd_back_cmd(cmd, new);
		i++;
	}
	new = *cmd;
	while(new != NULL)
	{
		printf("new->input = [%s]\n", new->input);
		printf("new->output = [%s]\n", new->output);
		new = new->next;
	}
	printf("-------------\n");
}

/*
**	free le nouveau tableau de string (ls -la)
** [1] ls
** [2] -la
*/

void			free_tmps(char **tabcmd, int i, t_temp *tmp)
{
	int			a;

	a = 0;
	while (tmp->strcmd[a])
		free(tmp->strcmd[a++]);
	free(tmp->strcmd);
	free(tabcmd[i]);
}

void			gestion_nani(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i] != NULL)
	{
		ft_printf("tab = [%s]\n", tab[i]);
		i++;
	}
}

/*
** Elle cherche dans le tableau de commandes, si la commande existe
** ensuite elle free la string du tableau free(tabcmd[i])
*/

static void		gestion_line(char **tabcmd, t_temp *tmp)
{
	int i;
	l_cmd	*cmd;

	i = -1;
	cmd = NULL;
	while (tabcmd[++i])
	{
		clean_str(tabcmd[i]);
		separator_string(&cmd, tabcmd[i], tmp);
		if (ft_strcmp(tabcmd[i], "exit") == 0)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		else if (ft_strncmp(tabcmd[i], "cd", 2) == 0)
			gestion_cd(tabcmd[i]);
		else if (ft_strcmp(tabcmd[i], "env") == 0)
			gestion_env(tmp);
		else if (ft_strcmp(tabcmd[i], "pwd") == 0)
			gestion_pwd(tabcmd, tmp, i);
		else if (ft_strncmp(tabcmd[i], "nani", 4) == 0)
			gestion_nani(tmp->strcmd);
		else if (ft_strcmp(tmp->strcmd[0], "export") == 0)
			gestion_export(tmp);
		/* else if (ft_strcmp(tmp->strcmd[0], "echo") == 0)
			gestion_echo(tabcmd[i], tmp->strcmd[1], tmp); */
		else if (command_bin(tmp->strcmd) == 0)
			;
		else if (tabcmd[i][0] == '\0')
			;
		else
			ft_printf("minishell: command not found: %s\n", tabcmd[i]);
		free_tmps(tabcmd, i, tmp);
	}
}

/*
** ft_getline reçoit avec l'aide du get_next_line la ligne avec les commandes...
** ...et lance aussi le parcing
*/

void			ft_getline(t_temp *tmp)
{
	char		*line;

	if (ft_gnl(0, &line) == -1 || (tmp->tabcmd = ft_split(line, ';')) == NULL)
		exit(1);
	gestion_line(tmp->tabcmd, tmp);
	free(tmp->tabcmd);
	free(line);
}
