#include "minishell.h"

int			search_error_pipe(t_cmd *tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tmp->input[i])
	{
		if (tmp->input[i] == '|')
			j++;
		i++;
	}
	if (j > 1)
		return (-1);
	return (i);
}

int			len_split3d(t_cmd *cmd)
{
	int		pipe;
	t_cmd	*tmp;

	tmp = cmd;
	pipe = 0;
	if (tmp && !ft_strcmp(tmp->input, "|"))
		return (-1);
	while (tmp)
	{	
		if (search_error_pipe(tmp) == -1)
			return (-1);
		if (!ft_strcmp(tmp->input, "|") && !tmp->next)
			return (-3);
		else if (!ft_strcmp(tmp->input, "|") && !ft_strcmp(tmp->next->input, " ") && !tmp->next->next)
			return (-1);
		else if (!ft_strcmp(tmp->input, "|") && !ft_strcmp(tmp->next->input, " ") && !ft_strcmp(tmp->next->next->input, "|"))
			return (-2);		
		else if (!ft_strcmp(tmp->input, "|") && ft_strcmp(tmp->next->input, " ") && !ft_strcmp(tmp->next->input, "|")) // si il y a un | et que celui d'apres et un | erreur
			return (-2);
		else if (!ft_strcmp(tmp->input, "|"))
			pipe++;
		tmp = tmp->next;
	}
	if (pipe == 0)
		return (0);
	return (pipe + 1);
}

int				len_tabsplit3d(t_cmd *cmd)
{
	t_cmd		*tmp;
	int			ret;

	ret = 0;
	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, "|"))
			return (ret);
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

void			tab2_3d(t_cmd *cmd, t_temp *tmp)
{
	t_cmd		*tmpo;
	int			i;
	int			k;
	int			len;


	i = 0;
	tmpo = cmd;
	while (tmpo)
	{
		k = 0;
		len = len_tabsplit3d(tmpo);
		tmp->outpipe[i] = (char**)malloc(sizeof(char *) * len + 1);
		tmp->inpipe[i] = (char**)malloc(sizeof(char *) * len + 1);
		while (k < len)
		{
			tmp->inpipe[i][k] = ft_strdup(tmpo->input);
			tmp->outpipe[i][k] = ft_strdup(tmpo->output);
			k++;
			if (tmpo->next)
				tmpo = tmpo->next;
		}
		tmp->outpipe[i][k] = NULL;		
		tmp->inpipe[i][k] = NULL;	
		i++;
		tmpo = tmpo->next;
	}
	tmp->outpipe[i] = NULL;
	tmp->inpipe[i] = NULL;
}

void			clean_tab2d(char **tabin, char **tabout)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	while (tabin[i])
	{
		if (!ft_strcmp(tabin[i], " "))
		{
			ft_free(tabin[i]);
			ft_free(tabout[i++]);
		}
		else
		{
			tabin[k] = tabin[i];
			tabout[k++] = tabout[i++];
		}
	}
	tabin[k] = 0;
	tabout[k] = 0;
}

void			clean_tab2d_echo(char **tabin, char **tabout)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	if (tabin[i])
	{
		if (!ft_strcmp(tabin[i], " "))
		{
			ft_free(tabin[i]);
			ft_free(tabout[i]);
			i++;
		}
		while (tabin[i])
		{
			tabin[k] = tabin[i];
			tabout[k] = tabout[i];
			i++;
			k++;
		}
		if (k > 0 && !ft_strcmp(tabin[k - 1], " "))   
		{
			ft_free(tabin[k - 1]);
			ft_free(tabout[k - 1]);
			tabin[k - 1] = 0;
			tabout[k - 1] = 0;
		}
		else
		{
			tabin[k] = 0;
			tabout[k] = 0;
		}
	}
}

void			clean_split3d(t_temp *tmp)
{
	int			i;

	i = 0;
	while (tmp->inpipe[i])
	{
		if (cherche_echo(tmp->outpipe[i]))
			clean_tab2d_echo(tmp->inpipe[i], tmp->outpipe[i]);
		else
			clean_tab2d(tmp->inpipe[i], tmp->outpipe[i]);
		i++;
	}
}

int				print_error(int ret)
{
	if (ret == -1 || ret == -2)
		write(1, "minishell: syntax error near unexpected token `|'\n", 50);
	if (ret == -3)
		write(1, "error multi ligne\n", 18);
	return (-1);
}

int				split3d(t_cmd *cmd, t_temp *tmp)
{
	int			ret;

	if ((ret = len_split3d(cmd)) == 0)//
		return (0);
	if (ret < 0)
	{
		return (print_error(ret));
	}
	tmp->outpipe = (char***)malloc(sizeof(char**) * ret + 1);
	tmp->inpipe = (char***)malloc(sizeof(char**) * ret + 1);
	tab2_3d(cmd, tmp);
	clean_split3d(tmp);
	return (1);
}
