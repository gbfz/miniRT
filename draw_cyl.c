#include "includes/minirt.h"

#include <stdio.h>
#include <unistd.h>

void			pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static float	min(float a, float b)
{
	if (a > b)
		return (b);
	return (a);
}

static float	get_lighting(t_light *light, float *p, float *n)
{
	
	float	lighting;
	float	light_ray[3];
	float	dot_n_l;

	lighting = 0;
	;
	while (light)
	{
		light_ray[0] = light->coords[0] - p[0];
		light_ray[1] = light->coords[1] - p[1];
		light_ray[2] = light->coords[2] - p[2];
		;
		normalize(light_ray);
		;
		dot_n_l = dot(n, light_ray);
		if (dot_n_l > 0)
			lighting += light->intensity * dot_n_l / (get_length(n) * get_length(light_ray));
		;
		light = light->next;
	}
	free(p);
	free(n);
	return (lighting);
}

static float	*get_coeff_light(t_light *light, float local_intensity)
{
	float *coeff_light;
	float denom;

	coeff_light = malloc(sizeof(float) * 3);
	;
	coeff_light[0] = 0;
	coeff_light[1] = 0;
	coeff_light[2] = 0;
	;
	denom = 0;
	;
	while (light)
	{
		coeff_light[0] += local_intensity * light->colors[0] / 255;
		coeff_light[1] += local_intensity * light->colors[1] / 255;
		coeff_light[2] += local_intensity * light->colors[2] / 255;
		;
		denom++;
		;
		light = light->next;
	}
	coeff_light[0] /= denom;
	coeff_light[1] /= denom;
	coeff_light[2] /= denom;
	return (coeff_light);
}

static int		get_color(float obj[3], t_amb *amb, t_light *light, float local_intensity)
{
	int		color;
	float	coeff_amb[3];
	float	*coeff_light;
	float	denom;

	coeff_amb[0] = amb->ratio * amb->colors[0] / 255;
	coeff_amb[1] = amb->ratio * amb->colors[1] / 255;
	coeff_amb[2] = amb->ratio * amb->colors[2] / 255;
	;
	coeff_light = get_coeff_light(light, local_intensity);
	;
	color = 0;
	color |= (int)min(255, obj[0] * (coeff_amb[0] + coeff_light[0])) << 16;
	color |= (int)min(255, obj[1] * (coeff_amb[1] + coeff_light[1])) << 8;
	color |= (int)min(255, obj[2] * (coeff_amb[2] + coeff_light[2]));
	;
	free(coeff_light);
	;
	return (color);
}

static float	*get_ray(int i, int j, float fov, t_res res)
{
	float	*ray;

	ray = malloc(sizeof(float) * 3);
	;
	ray[0] = (j - res.x / 2);
	ray[1] = -(i - res.y / 2);
	ray[2] = res.x / (2 * tan(fov / 2));
	;
	normalize(ray);
	;
	return (ray);
}

static float	*get_difference(float centre[3])
{
	float	*difference;

	difference = malloc(sizeof(float) * 3);
	;
	difference[0] = -centre[0];
	difference[1] = -centre[1];
	difference[2] = -centre[2];
	;
	return (difference);
}

static float	*get_bottom_cap(t_cylinder *cyl)
{
	float *bottom_cap;

	bottom_cap = malloc(sizeof(float) * 3);
	bottom_cap[0] = cyl->coords[0] - cyl->vector[0] * (cyl->height / 2);
	bottom_cap[1] = cyl->coords[1] - cyl->vector[1] * (cyl->height / 2);
	bottom_cap[2] = cyl->coords[2] - cyl->vector[2] * (cyl->height / 2);
	;
	return (bottom_cap);
}

static float	*get_top_cap(t_cylinder *cyl)
{
	float *top_cap;

	top_cap = malloc(sizeof(float) * 3);
	top_cap[0] = cyl->coords[0] + cyl->vector[0] * (cyl->height / 2);
	top_cap[1] = cyl->coords[1] + cyl->vector[1] * (cyl->height / 2);
	top_cap[2] = cyl->coords[2] + cyl->vector[2] * (cyl->height / 2);
	;
	return (top_cap);
}

static int		check_borders(t_cylinder *cyl, float t, float ray[3], float o_c[3])
{
	float	m;
	float	poa[3];
	float	*bottom_cap;
	float	*top_cap;
	int		res;

	m = dot(ray, cyl->vector) * t + dot(o_c, cyl->vector);
	;
	bottom_cap = get_bottom_cap(cyl);
	poa[0] = bottom_cap[0] + cyl->vector[0] * m;
	poa[1] = bottom_cap[1] + cyl->vector[1] * m;
	poa[2] = bottom_cap[2] + cyl->vector[2] * m;
	;
	top_cap = get_top_cap(cyl);
	;
	res = 0;
	if (poa[0] >= bottom_cap[0] && poa[1] >= bottom_cap[1] && poa[2] >= bottom_cap[2] &&
		poa[0] <= top_cap[0] && poa[1] <= top_cap[1] && poa[2] <= top_cap[2])
		res = 1;
	free(bottom_cap);
	free(top_cap);
	return (res);
}

static float	*get_point(float ray[3], float t)
{
	float *point;

	point = malloc(sizeof(float) * 3);
	point[0] = ray[0] * t;
	point[1] = ray[1] * t;
	point[2] = ray[2] * t;
	;
	return (point);
}

static float	*get_normal(float point[3], float centre[3])
{
	float *normal;

	normal = malloc(sizeof(float) * 3);
	normal[0] = point[0] - centre[0];
	normal[1] = point[1] - centre[1];
	normal[2] = point[2] - centre[2];
	;
	normalize(normal);
	;
	return (normal);
}

static int		intersection(t_cylinder *cyl, float ray[3], float **p, float **n)
{
	float eq[3];
	float o_c[3];
	float disc;
	float t[3];

	o_c[0] = -cyl->coords[0];
	o_c[1] = -cyl->coords[1];
	o_c[2] = -cyl->coords[2];
	eq[0] = dot(ray, ray) - pow(dot(ray, cyl->vector), 2);
	eq[1] = (dot(ray, o_c) - dot(ray, cyl->vector) * dot(o_c, cyl->vector)) * 2;
	eq[2] = dot(o_c, o_c) - pow(dot(o_c, cyl->vector), 2) - pow(cyl->diameter / 2, 2);
	disc = eq[1] * eq[1] - 4 * eq[0] * eq[2];
	if (disc < 0)
		return (0);
	t[1] = (-eq[1] - sqrt(disc)) / (2 * eq[0]);
	t[2] = (-eq[1] + sqrt(disc)) / (2 * eq[0]);
	if (check_borders(cyl, t[1], ray, o_c) == 1)
		t[0] = t[1];
	else if (check_borders(cyl, t[2], ray, o_c) == 1)
		t[0] = t[2];
	else
		return (0);
	*p = get_point(ray, t[0]);
	*n = get_normal(*p, cyl->coords);
	return (1);
}

void			draw_cylinder(void *obj, t_scene *scene, t_img *img)
{
	t_cylinder	*cy;
	int			color;
	int			i;
	int			j;
	int			fov;
	float		*ray;
	float		lighting;
	float		*p;
	float		*n;

	cy = (t_cylinder *)obj;
	fov = scene->cam->angle * M_PI / 180;
	i = 0;
	while (i < scene->res.y)
	{
		j = 0;
		while (j < scene->res.x)
		{
			ray = get_ray(i, j, fov, scene->res);
			if (intersection(cy, ray, &p, &n) == 1)
			{
				lighting = get_lighting(scene->light, p, n);
				color = get_color(cy->colors, scene->amb, scene->light, lighting);
				if (p[0] == cy->coords[0] && p[1] == cy->coords[1] && p[2] == cy->coords[2])
					pixel_put(img, j, i, 0x00FFFFFF);
				else
					pixel_put(img, j, i, color);
			}
			free(ray);
			j++;
		}
		i++;
	}
}

int				main(int ac, char **av)
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		*scene;
	int			config;

	if (check_file(ac, av[1]) == -1)
		return (1);
	config = open(av[1], O_RDONLY);
	scene = parser(config);
	close(config);
	if (scene == NULL)
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, scene->res.x, scene->res.y, "kruzhochek");
	img.img = mlx_new_image(mlx, scene->res.x, scene->res.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.en);
	printf("\n 11111111111111\n\n");
	draw_cylinder(scene->obj_lst->obj, scene, &img);
	//free(scene->amb->colors);
	//free(scene->amb);
	//free(scene->cam);
	//free(scene->obj_lst->obj);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}