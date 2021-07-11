#include "../../includes/parser.h"

size_t	doublelen(char *line)
{
	size_t	i;

	i = 0;
	if (line[i] == '-')
		i++;
	if (line[i] == '+')
		i++;
	while ((ft_isdigit(line[i]) || line[i] == '.') && line[i])
		i++;
	return (i);
}

int		count_words(char *line)
{
	int words;

	words = 0;
	while (*line)
	{
		if (ft_isnumber(line))
			words++;
		line += doublelen(line);
		while (!ft_isdigit(*line) && *line)
			line++;
	}
	return (words);
}
