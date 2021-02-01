/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:54:07 by meldora           #+#    #+#             */
/*   Updated: 2021/01/26 11:29:10 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <unistd.h>

# include "objects.h"
# include "scene.h"
# include "parser.h"
# include "vector_operations.h"
# include "quaternion_operations.h"
# include "matrix_operations.h"
# include "../minilibx_mms_20200219/mlx.h"

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

void	pixel_put(t_img *img, int x, int y, int color);

#endif
