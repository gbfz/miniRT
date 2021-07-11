#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

int		ft_init(char **line, char **buf, int *was_read);
int		ft_exit(int was_read, char **buf);
char	*ft_strappend(char *s, char c);
int		get_next_line(int fd, char **line);

#endif
