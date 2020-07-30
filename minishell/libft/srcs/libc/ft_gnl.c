/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 02:15:57 by corozco           #+#    #+#             */
/*   Updated: 2020/01/15 02:32:59 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void		ft_subs(char data[])
{
	long		i;
	long		j;
	char		cpy[BS_GNL + 1];

	i = 0;
	while (i < BS_GNL + 1)
		cpy[i++] = '\0';
	i = 0;
	while (data[i] != '\n' && i < BS_GNL && data[i] != '\0')
		i++;
	if (data[i] == '\n')
		i++;
	j = 0;
	while (i < BS_GNL)
		cpy[j++] = data[i++];
	i = -1;
	while (++i < BS_GNL)
		data[i] = cpy[i];
	data[i] = '\0';
}

static int		check_file(int fd, char files[][BS_GNL + 1])
{
	long		len;
	long		ret;

	if (fd < 0 || fd > 256)
		return (-1);
	len = 0;
	while (files[fd][len] && files[fd][len] != '\n' && len < BS_GNL)
		len++;
	if (len > 0 || files[fd][len] == '\n')
		return (len);
	if ((ret = read(fd, files[fd], BS_GNL)) < 0)
		return (ret);
	len = 0;
	while (files[fd][len] != '\n' && len < ret)
		len++;
	return (len);
}

static int		changes_buffer(int size, int length, char **line, char data[])
{
	long		i;
	char		cpy[size];

	i = -1;
	while (++i < size - length)
		cpy[i] = (*line)[i];
	i = -1;
	while (++i + (size - length) < size)
		cpy[i + (size - length)] = data[i];
	free((*line));
	if (!((*line) = malloc(sizeof(char) *
					(size + ((data[length] == '\n' || !length) ? 1 : 0)))))
		return (-1);
	i = -1;
	while (++i < size)
		(*line)[i] = cpy[i];
	if (!(i *= 0) && (data[length] == '\n' || !length))
	{
		(*line)[size] = '\0';
		ft_subs(data);
		return (1);
	}
	while ((data[length] != '\n' || length) && i < BS_GNL)
		data[i++] = '\0';
	return (0);
}

int				ft_gnl(int fd, char **line)
{
	int			length;
	int			size;
	static char	files[256][BS_GNL + 1];

	if (!line || BS_GNL <= 0 || !((*line) = malloc(sizeof(char)))
		|| (length = check_file(fd, files)) < 0)
		return (-1);
	if (!length && files[fd][length] != '\n')
		(*line)[0] = '\0';
	size = 0;
	while ((size += length) > -1 && (length || files[fd][length] == '\n'))
	{
		if ((length = changes_buffer(size, length, line, files[fd])) != 0)
			return (length);
		if ((length = check_file(fd, files)) < 0)
			return (length);
	}
	if (size > 0)
		if (changes_buffer(size, length, line, files[fd]) < 0)
			return (-1);
	return (0);
}
