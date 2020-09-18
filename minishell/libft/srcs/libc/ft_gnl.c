/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 23:30:58 by corozco           #+#    #+#             */
/*   Updated: 2020/09/18 13:31:37 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int				fbo0(char *buf, int *i)
{
	while (buf[*i] && buf[*i] != '\n')
		(*i)++;
	if (buf[*i] == '\n')
		return (1);
	return (0);
}

int				update_line(char **line, char *buf, int i)
{
	int			k;
	int			len;
	int			len_initial;
	char		*tmp;

	tmp = *line;
	len_initial = ft_strlen(tmp);
	len = len_initial + i;
	k = -1;
	if (!(*line = malloc(sizeof(char) * len + 1)))
		return (-1);
	while (++k < len)
	{
		if (k < len_initial)
			line[0][k] = tmp[k];
		else
			line[0][k] = buf[k - len_initial];
	}
	line[0][k] = '\0';
	free(tmp);
	return (1);
}

int				update_buf(char *buf, int i)
{
	int			k;

	k = 0;
	if (buf[i] == '\n')
		i++;
	while (buf[i])
		buf[k++] = buf[i++];
	buf[k] = '\0';
	return (0);
}

int				ft_gnl(int fd, char **line)
{
	static char	buf[BS_GNL + 1] = {'\0'};
	int			ret;
	int			i;
	int			found;

	*line = NULL;
	if (!line || fd < 0 || BS_GNL <= 0 || (read(fd, &buf, 0)) == -1)
		return (-1);
	i = 0;
	found = fbo0(buf, &i);
	if (update_line(line, buf, i) == -1)
		return (-1);
	if (!(update_buf(buf, i)) && found == 1)
		return (1);
	while ((ret = read(fd, buf, BS_GNL)) > 0)
	{
		i = 0;
		buf[ret] = '\0';
		found = fbo0(buf, &i);
		if (update_line(line, buf, i) == -1)
			return (-1);
		if (!(update_buf(buf, i)) && found == 1)
			return (1);
	}
	return (ret);
}
