/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/04 00:14:24 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     command_bin(char *str)
{
    char **tab;
    char *new_env[] = {NULL};
    //printf("str = [%s]\n", str);
    char *command;
    int i;
    pid_t f;

    f = fork();
    i = 0;
    tab = ft_split(str, ' ');
    if (!(command = (char*)malloc(sizeof(char) * ft_strlen(str) + 6)))
        return(0);
    command[0] = '/';
    command[1] = 'b';
    command[2] = 'i';
    command[3] = 'n';
    command[4] = '/';
    while (str[i] != '\0')
    {
        command[i + 5] = str[i];
        i++;
    }
    command[i + 5] = '\0';
    //printf("command = [%s]\n", command);
    int a;
    a = 0;
/*    while (tab[a] != NULL)
    {
        printf("tab[%d] = {%s}\n", a , tab[a]);
        a++;
    }
    a = 0;
    while (envp[a] != NULL)
    {
        printf("envp[%d] = {%s}\n", a , envp[a]);
        a++;
    } */
    if (f == 0)
    {
        if (execve(command, tab, new_env) == -1)
        {
            free(command);
            return (1);
        }
        return(1);
    }
    wait(&f);
    free(command);
    return (0);
}
