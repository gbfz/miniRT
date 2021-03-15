/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:31:52 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:43:49 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strappend(char *s, char c)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	res[++i] = '\0';
	free(s);
	return (res);
}

static int	ft_line(char **line, char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		*line = ft_strappend(*line, buf[i]);
		if (*line == NULL)
			return (-1);
		i++;
	}
	return (i);
}

static int	read_rem(char **line, char **rem)
{
	int was_written;

	if ((*rem)[0] == '\n')
		(*rem)++;
	was_written = ft_line(line, *rem);
	if (was_written == -1)
		return (-1);
	*rem += was_written;
	if ((*rem)[0] == '\0')
		*rem = NULL;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char		*buf[256];
	static char		*rem[256];
	int				was_read;
	int				was_written;

	if (fd < 0 || fd > 256)
		return (-1);
	if (ft_init(line, &buf[fd], &was_read) == -1)
		return (-1);
	if (rem[fd] != NULL)
		if ((was_read = read_rem(line, &rem[fd])) == -1)
			return (ft_exit(-1, &buf[fd]));
	if (rem[fd] == NULL)
		while ((was_read = read(fd, buf[fd], BUFFER_SIZE)) != 0)
		{
			if (was_read == -1)
				return (ft_exit(-1, &buf[fd]));
			buf[fd][was_read] = '\0';
			if ((was_written = ft_line(line, buf[fd])) == -1)
				return (ft_exit(-1, &buf[fd]));
			rem[fd] = buf[fd] + was_written;
			if (buf[fd][was_written] == '\n')
				break ;
		}
	return (ft_exit(was_read, &buf[fd]));
}
