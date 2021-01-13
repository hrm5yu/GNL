/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirama <shirama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:50:58 by shirama           #+#    #+#             */
/*   Updated: 2021/01/12 14:37:16 by shirama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		safe_free(char **p, int rt)
{
	if (*p != NULL)
	{
		free(*p);
		*p = NULL;
	}
	return (rt);
}

int		put_line(char **line, char **memo, char *buf)
{
	char	*tmp;
	size_t	len;

	len = ft_strchr(buf, '\n');
	tmp = *line;
	if (!(*line = ft_strjoin(*line, buf, len)))
		return (safe_free(&tmp, -1));
	safe_free(&tmp, 1);
	if (buf[len] == '\n')
	{
		tmp = *memo;
		if (!(*memo = ft_strdup(&buf[len + 1])))
			return (safe_free(&tmp, -1));
		return (safe_free(&tmp, 1));
	}
	return (safe_free(memo, 0));
}

int		get_next_line(int fd, char **line)
{
	static char *memo[256];
	int			rt;
	char		*buf;
	ssize_t		n;

	n = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || fd >= 256)
		return (-1);
	rt = 0;
	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	if (memo[fd])
		rt = put_line(line, &memo[fd], memo[fd]);
	if (!(buf = malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1)))
		rt = -1;
	while (rt == 0 && (n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = '\0';
		if (n == 0 || (rt = put_line(line, &memo[fd], buf)) == -1)
			break ;
	}
	if (n == -1)
		rt = -1;
	return (safe_free(&buf, rt));
}
