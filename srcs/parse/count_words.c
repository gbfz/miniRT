/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:00:20 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 13:39:41 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
