/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:42:05 by lusargsy          #+#    #+#             */
/*   Updated: 2021/02/28 20:45:29 by lusargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*find_new_line(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s && s[i] != '\0' && s[i] != '\n')
		i++;
	if (!(ret = malloc((i + 1))))
		return (NULL);
	i = 0;
	while (s && s[i] != '\0' && s[i] != '\n')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*static_mas(char *st)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	if (!st)
		return (NULL);
	while (st[i] != '\0' && st[i] != '\n')
		i++;
	if (st[i] == '\0')
	{
		free(st);
		return (NULL);
	}
	if (!(ptr = malloc(((ft_strlen(st) - i) + 1))))
		return (NULL);
	i++;
	j = 0;
	while (st[i] != '\0')
		ptr[j++] = st[i++];
	ptr[j] = '\0';
	free(st);
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	int			r;
	char		*buf;
	static char	*c;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	r = 1;
	while ((r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		c = ft_strjoin(c, buf);
		if (ft_strchr(buf, '\n') || ft_strchr(c, '\0'))
			break ;
	}
	free(buf);
	if (r < 0)
		return (-1);
	*line = find_new_line(c);
	c = static_mas(c);
	if (r == 0 && !c)
		return (0);
	return (1);
}
