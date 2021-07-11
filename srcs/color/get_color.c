#include "../../includes/minirt.h"

static double	min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

static double	*get_coeff_light(t_light *light, t_params *obj,
		 t_cam *cam, t_scene *scene)
{
	double	*coeff_light;
	double	local_intensity;

	coeff_light = ft_calloc(sizeof(double), 3);
	while (light)
	{
		local_intensity = get_intensity(light, obj, cam, scene);
		coeff_light[0] += local_intensity * light->colors[0] / 255;
		coeff_light[1] += local_intensity * light->colors[1] / 255;
		coeff_light[2] += local_intensity * light->colors[2] / 255;
		light = light->next;
	}
	free(obj->point);
	free(obj->normal);
	return (coeff_light);
}

int	get_color(t_params *obj, t_scene *scene, t_cam *cam)
{
	int	color;
	double	coeff_amb[3];
	double	*coeff_light;

	coeff_amb[0] = scene->amb->ratio * scene->amb->colors[0] / 255;
	coeff_amb[1] = scene->amb->ratio * scene->amb->colors[1] / 255;
	coeff_amb[2] = scene->amb->ratio * scene->amb->colors[2] / 255;
	coeff_light = get_coeff_light(scene->light, obj, cam, scene);
	color = 0;
	color |= ((int)min(obj->colors[0] *
			  (coeff_amb[0] + coeff_light[0]), 255)) << 16;
	color |= ((int)min(obj->colors[1] *
			  (coeff_amb[1] + coeff_light[1]), 255)) << 8;
	color |= ((int)min(obj->colors[2] *
			   (coeff_amb[2] + coeff_light[2]), 255));
	free(coeff_light);
	return (color);
}
