/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amblient_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:09:15 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 16:20:48 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../alt_libft/alt_libft.h"

static int	check_amb_line(char *line)
{
	if (count_words(line) != 4)
		return (1);
	skip_spaces(&line);
	if (ft_isdigit(*line))
		line += doublelen(line);
	else
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

void	*parse_amb(char *line, t_scene *scene)
{
	if (check_amb_line(line))
		exit_error("Wrong values for ambient lighting");
	scene->amb = malloc(sizeof(t_amb));
	skip_spaces(&line);
	scene->amb->ratio = ft_atof(line);
	if (scene->amb->ratio < 0 || scene->amb->ratio > 1)
		exit_error("Wrong values for amblient lighting intensity");
	line += doublelen(line);
	skip_spaces(&line);
	scene->amb->colors = parse_colors(&line);
	if (scene->amb->colors == NULL)
		exit_error("Wrong values for ambient lighting colors");
	return (scene);
}