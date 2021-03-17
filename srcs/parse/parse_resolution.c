/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:03:03 by meldora           #+#    #+#             */
/*   Updated: 2021/03/17 18:35:58 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../list_management/alt_libft.h"

static int	check_res_line(char *line)
{
	if (count_words(line) != 2)
		return (1);
	skip_spaces(&line);
	while (*line == '-' || *line == '+')
		line++;
	if (ft_isdigit(*line))
		while (ft_isdigit(*line))
			line++;
	else
		return (1);
	skip_spaces(&line);
	while (*line == '-' || *line == '+')
		line++;
	if (ft_isdigit(*line))
		while (ft_isdigit(*line))
			line++;
	else
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

static int	ft_atoi_for_mlx(char **s)
{
	int res;
	int sign;

	sign = 1;
	while (**s == '-' || **s == '+')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	res = 0;
	while (ft_isdigit(**s))
	{
		if (res <= 16384)
			res = res * 10 + (**s - '0');
		(*s)++;
	}
	return (res * sign);
}

void		*parse_res(char *line, t_scene *scene)
{
	if (check_res_line(line))
		exit_error("Wrong values for resolution");
	scene->res = malloc(sizeof(t_res));
	if (scene->res == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	scene->res->x = ft_atoi_for_mlx(&line);
	if (scene->res->x < 0)
		exit_error("Wrong image width");
	while (ft_isdigit(*line))
		line++;
	skip_spaces(&line);
	scene->res->y = ft_atoi_for_mlx(&line);
	if (scene->res->y < 0)
		exit_error("Wrong image height");
	return (scene);
}
