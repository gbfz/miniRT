#include "../../includes/parser.h"

static int	ft_isfloat(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	return (1);
}

int		ft_isnumber(char *str)
{
	int		size;
	char	*save;

	save = str;
	if (*str == '-' || *str == '+')
		str++;
	size = 0;
	if (ft_isdigit(*str))
		while (ft_isdigit(*str))
		{
			str++;
			size++;
		}
	else
		return (0);
	if (*str == '.')
		return (ft_isfloat(save));
	if (size == 0)
		return (0);
	return (1);
}

static int	check_block(char **line)
{
	if (ft_isnumber(*line))
		while (ft_isdigit(**line) || **line == '.' ||
				  **line == '-' || **line == '+')
			(*line)++;
	else
		return (1);
	return (0);
}

int			check_group(char **line)
{
	if (check_block(line))
		return (1);
	skip_spaces(line);
	if (**line == ',')
		(*line)++;
	skip_spaces(line);
	if (check_block(line))
		return (1);
	skip_spaces(line);
	if (**line == ',')
		(*line)++;
	skip_spaces(line);
	if (check_block(line))
		return (1);
	return (0);
}
