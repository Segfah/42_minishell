/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/03 20:43:26 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     command_bin(char *str, char **av, char **envp)
{
    char *command;
    int i;
    pid_t f;

    f = fork();
    i = 0;
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
    /* 
    int a;
    a = 0;
    while (av[a] != NULL)
    {
        printf("av[%d] = {%s}\n", a , av[a]);
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
        if (execve(command, av, envp) == -1)
        {
            free(command);
            return (0);
        }
        return(1);
    }
    free(command);
    return (1);
}