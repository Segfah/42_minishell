/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 22:10:58 by lryst             #+#    #+#             */
/*   Updated: 2020/08/03 20:39:11 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

void			gestion_cd(char *str)
{
	char		*path;
	int			i;

	i = 2;
	if (ft_strncmp(str, "cd ", 3) == 0)
	{
		if (!(path = (char*)malloc(sizeof(char) * ft_strlen(str) - 2)))
		{
			ft_printf("gestion_cd2, error malloc\n");
			exit(0);
		}
		while (str[i++] != '\0')
			path[i - 3] = str[i];
		if (chdir(path) != 0)
			ft_printf("cd: %s: %s\n", strerror(errno), path);
		free(path);
	}
}
