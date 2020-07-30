/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:00:46 by corozco           #+#    #+#             */
/*   Updated: 2020/07/31 00:41:46 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			welcome2(void)
{
	write(1, "        .__       .__       .__           .__  .__   \n", 54);
	write(1, "  _____ |__| ____ |__| _____|  |__   ____ |  | |  |  \n", 54);
	write(1, " /     \\|  |/    \\|  |/  ___/  |  \\_/ __ \\|  | |  |  \n", 54);
	write(1, "|  Y Y  \\  |   |  \\  |\\___ \\|   Y  \\  ___/|  |_|  ", 50);
	write(1, "|__\n", 4);
	write(1, "|__|_|  /__|___|  /__/____  >___|  /\\___  >____/____/\n", 54);
	write(1, "      \\/        \\/        \\/     \\/     \\/       \n", 50);
}

void			welcome(void)
{
	write(1, "                   / \\              \n", 37);
	write(1, "                  / _ \\             \n", 37);
	write(1, "                 | / \\ |            \n", 37);
	write(1, "                 ||   || _______    \n", 37);
	write(1, "                 ||   || |\\     \\   \n", 37);
	write(1, "                 ||   || ||\\     \\  \n", 37);
	write(1, "                 ||   || || \\    |  \n", 37);
	write(1, "                 ||   || ||  \\__/   \n", 37);
	write(1, "                 ||   || ||   ||    \n", 37);
	write(1, "                  \\\\_/ \\_/ \\_//     \n", 37);
	write(1, "                 /   _     _   \\    \n", 37);
	write(1, "                /               \\   \n", 37);
	write(1, "                |    O     O    |   \n", 37);
	write(1, "                |   \\  ___  /   |   \n", 37);
	write(1, "               /     \\ \\_/ /     \\  \n", 37);
	write(1, "              /  -----  |  --\\    \\ \n", 37);
	write(1, "              |     \\__/|\\__/ \\   | \n", 37);
	write(1, "              \\       |_|_|       / \n", 37);
	write(1, "               \\_____       _____/  \n", 37);
	write(1, "                     \\     /        \n\n", 38);
	welcome2();
}

/*
** Fonction utilisée pour faire le prompt
** elle sert à prendre le path à partir du dernier '/'
** Example 1:
** char *str = "/Users/&(USER)/Documents/42/42_minishell/minishell" , c = '/'
** le return ->     "/minishell"         (chaine malloc)
** Example 2: imaginant qu'on est dans la racine 'cd /'
** char *str = "/" c = '/'
** le return ->     "/"                  (chaine malloc)
*/

char			*ft_strrev(char *str)
{
	int			i;

	if (str)
	{
		i = ft_strlen(str);
		if (i == 1)
			if (str[0] == '/')
				return (ft_strdup("/"));
		while (0 <= i--)
			if (str[i] == '/')
				return (ft_strdup(&str[++i]));
	}
	return (NULL);
}

/*
** is_a_cmd reçoit avec l'aide du get_next_line la ligne avec les commandes...
** ...et lance aussi le parcing
*/

void			is_a_cmd(t_temp *tmp)
{
	char		*line;

	if (ft_gnl(0, &line) == -1)
		exit(1);
	// ----------------------------------------------------------------------------------------------------------------------COROZCO
	(void)tmp; // supprimer et faire une fonction parcing -------------------------------------------------------------------COROZCO
	// ----------------------------------------------------------------------------------------------------------------------COROZCO
	free(line);
}

/*
** On recalcule le prompt à chaque fois car le path(pwd) va changer quand...
** ...on fait un cd (cd .., cd, cd ~, etc) de cette maniere on aura...
** ...le prompt maj
** ps (trouver une autre maniere de le faire sans fais autant d'appel à getcwd)
*/

int				launcher(t_temp tmp)
{
	char		*prompt;

	while (1)
	{
		tmp.env = getcwd(NULL, 0);
		prompt = ft_strrev(tmp.env);
		ft_printf("\x1b[33m%s\x1b[0m🐰: ", prompt);
		free(tmp.env);
		is_a_cmd(&tmp);
		free(prompt);
	}
}

/*
** tmp.env = variable qui prend le getcwd (get working directory pathname)(pwd);
** launcher = fonction principal (boucle infini)
*/

int		main(int ac, char **av, char **envp)
{
	t_temp	tmp;

	welcome();
	tmp.env = getcwd(NULL, 0);
	launcher(tmp);
	(void)ac;
	(void)av;
	(void)envp;
	return (0);
}
