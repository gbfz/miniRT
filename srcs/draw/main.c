/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:34:06 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 19:34:25 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int				main(int ac, char **av)
{
	t_data		data;
	t_scene		*scene;
	int			config;

	check_file(ac, av);
	config = open(av[1], O_RDONLY);
	if (config == -1)
		exit_error("Failed to open .rt file");
	scene = parser(config);
	init_data(&data, scene);
	render(&data, scene);
	display(&data);
	return (0);
}