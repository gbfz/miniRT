/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:58:15 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 14:12:08 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../alt_libft/alt_libft.h"

void	skip_spaces(char **line)
{
	while (ft_isspace(**line) && **line)
		(*line)++;
}

double	*parse_coords(char **line)
{
	double	*coords;
	short	i;

	coords = malloc(sizeof(double) * 3);
	i = 0;
	while (i <= 2)
	{
		coords[i] = ft_atof(*line);
		*line += doublelen(*line) + 1;
		skip_spaces(line);
		if (**line == ',')
			(*line)++;
		skip_spaces(line);
		i++;
	}
	return (coords);
}

double	*parse_vector(char **line)
{
	double	*vector;
	short	i;
	double	len;

	vector = malloc(sizeof(double) * 3);
	i = 0;
	while (i <= 2)
	{
		vector[i] = ft_atof(*line);
		if (vector[i] > 1 || vector[i] < -1)
		{
			free(vector);
			return (NULL);
		}
		*line += doublelen(*line) + 1;
		skip_spaces(line);
		if (**line == ',')
			(*line)++;
		skip_spaces(line);
		i++;
	}
	len = get_length(vector);
	if (len < 0.9999 || len > 1.0001)
	{
		free(vector);
		return (NULL);
	}
	return (vector);
}

double	*parse_colors(char **line)
{
	double	*colors;
	short	i;

	colors = malloc(sizeof(double) * 3);
	i = 0;
	while (i <= 2)
	{
		colors[i] = ft_atof(*line);
		if (colors[i] < 0 || colors[i] > 255)
		{
			free(colors);
			return (NULL);
		}
		*line += doublelen(*line) + 1;
		skip_spaces(line);
		if (**line == ',')
			(*line)++;
		skip_spaces(line);
		i++;
	}
	return (colors);
}