#include "get_next_line.h"

int		ft_init(char **line, char **buf, int *was_read)
{
	*line = (char *)malloc(1);
	(*line)[0] = '\0';
	if (BUFFER_SIZE <= 0)
		return (-1);
	if (*buf == NULL)
	{
		*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (*buf == NULL)
			return (-1);
	}
	*was_read = 0;
	return (0);
}

int		ft_exit(int was_read, char **buf)
{
	if (was_read >= 1)
		return (1);
	free(*buf);
	*buf = NULL;
	if (was_read == 0)
		return (0);
	return (-1);
}
