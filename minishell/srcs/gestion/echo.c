/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:54:35 by lryst             #+#    #+#             */
/*   Updated: 2020/08/06 01:04:25 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    gestion_echo(char *str)
{
    char *cmd;
    char **tab;
    int i;
    int j;

    i = 4;
    j = 0;
    while (str[i++] != '\0')
        j++;
    if (!(cmd = (char*)malloc(sizeof(char) * j + 1)))
        return ;
    i = 4;
    j = 0;
    while (str[i] != '\0')
    {
        cmd[j++] = str[i++];
    }
    cmd[j] = '\0';
    tab = ft_split_echo(cmd, ' ');
    i = 0;
    while (tab[i] != NULL)
    {
        ft_printf("%s", tab[i]);
        i++;
    }
    ft_printf("\n");

}