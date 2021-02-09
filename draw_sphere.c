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

static float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

static void		move(t_sphere *sphere, t_cam cam)
{
	sphere->coords[0] += fabs(cam.coords[0]);
	sphere->coords[1] += fabs(cam.coords[1]);
	sphere->coords[2] += fabs(cam.coords[2]);
}

static void		rotate(t_sphere *sphere, float cam[3])
{
	float	*quaternion;
	float	**matrix;
	float	default_camera_direction[3];

	default_camera_direction[0] = 0;
	default_camera_direction[1] = 0;
	default_camera_direction[2] = 1;
	;
	quaternion = get_quaternion(cam, default_camera_direction);
	matrix = matrix_from_quaternion(quaternion);
	multiply_coords_by_matrix(sphere->coords, matrix);
	;
	free(quaternion);
	free_matrix(matrix);
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

static short	intersection(t_sphere *sphere, float ray[3], float **p, float **n)
{
	float	b;
	float	c;
	float	*difference;
	float	delta;
	float	t;

	difference = get_difference(sphere->coords);
	b = 2 * dot(ray, difference);
	c = dot(difference, difference) - pow(sphere->diameter / 2, 2);
	free(difference);
	delta = b * b - 4 * c;
	if (delta < 0)
		return (0);
	if ((-b + sqrt(delta) / 2) < 0)
		return (0);
	if ((-b - sqrt(delta)) / 2 > 0)
		t = (-b - sqrt(delta)) / 2;
	else
		t = (-b + sqrt(delta)) / 2;
	;
	*p = malloc(sizeof(float) * 3);
	(*p)[0] = t * ray[0];
	(*p)[1] = t * ray[1];
	(*p)[2] = t * ray[2];
	;
	*n = malloc(sizeof(float) * 3);
	(*n)[0] = (*p)[0] - sphere->coords[0];
	(*n)[1] = (*p)[1] - sphere->coords[1];
	(*n)[2] = (*p)[2] - sphere->coords[2];
	normalize(*n);
	;
	return (1);
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

void			draw_sphere(void *obj, t_scene *scene, t_img *img)
{
	t_sphere	*sphere;
	int			color;
	float		*ray;
	float		fov;
	int			i;
	int			j;
	float		*p;
	float		*n;
	float		lighting;
	int k = 0;

	sphere = (t_sphere *)obj;
	fov = scene->cam->angle * M_PI / 180;
	move(sphere, *scene->cam);
	rotate(sphere, scene->cam->vector);
	i = 0;
	while (i < scene->res.y)
	{
		j = 0;
		while (j < scene->res.x)
		{
			ray = get_ray(i, j, fov, scene->res);
			if (intersection(sphere, ray, &p, &n) == 1)
			{
				lighting = get_lighting(scene->light, p, n);
				color = get_color(sphere->colors, scene->amb, scene->light, lighting);
				pixel_put(img, j, i, color);
				k++;
			}
			free(ray);
			j++;
		}
		i++;
	}
	free(sphere->coords);
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
	draw_sphere(scene->obj_lst->obj, scene, &img);
	printf("\n 22222222222222\n\n");
	draw_sphere(scene->obj_lst->next->obj, scene, &img);
	printf("\n 33333333333333\n\n");
	draw_sphere(scene->obj_lst->next->next->obj, scene, &img);
	free(scene->amb->colors);
	free(scene->amb);
	free(scene->cam);
	free(scene->obj_lst->obj);
	free(scene->obj_lst->next->obj);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
