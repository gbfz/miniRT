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
	return (lighting);
}

static float	*get_coeff_light(t_light *light, float local_intensity)
{
	float *coeff_light;
	float denom;

	coeff_light = malloc(sizeof(float) * 3);
	coeff_light[0] = 0;
	coeff_light[1] = 0;
	coeff_light[2] = 0;
	;
	denom = 0;
	while (light)
	{
		coeff_light[0] += local_intensity * light->colors[0] / 255;
		coeff_light[1] += local_intensity * light->colors[1] / 255;
		coeff_light[2] += local_intensity * light->colors[2] / 255;
		denom++;
		light = light->next;
	}
	coeff_light[0] /= denom;
	coeff_light[1] /= denom;
	coeff_light[2] /= denom;
	;
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

static float	*get_rand_vec(float v[3])
{
	float *rand_vec;

	rand_vec = malloc(sizeof(float) * 3);
	;
	rand_vec[0] = v[2];
	rand_vec[1] = v[0];
	rand_vec[2] = v[1];
	;
	return (rand_vec);
}

static float	**alloc_vertices(void)
{
	float **vertices;

	vertices = malloc(sizeof(*vertices) * 4);
	vertices[0] = malloc(sizeof(float) * 3);
	vertices[1] = malloc(sizeof(float) * 3);
	vertices[2] = malloc(sizeof(float) * 3);
	vertices[3] = malloc(sizeof(float) * 3);
	return (vertices);
}

static void		get_planes(float vector[3], float rand_vec[3], float **plane, float **c)
{
	*plane = cross(vector, rand_vec);
	normalize(*plane);
	*c = cross(vector, *plane);
	normalize(*c);
}

static float	**get_vertices(t_square *sq)
{
	float **vertices;
	float *rand_vec;
	float *plane;
	float *c;
	float half_side;

	vertices = alloc_vertices();
	rand_vec = get_rand_vec(sq->vector);
	get_planes(sq->vector, rand_vec, &plane, &c);
	half_side = sq->side / 2;
	// left bottom
	vertices[0][0] = (sq->coords[0] - half_side * plane[0]) + (half_side * c[0]);
	vertices[0][1] = (sq->coords[1] - half_side * plane[1]) + (half_side * c[1]);
	vertices[0][2] = (sq->coords[2] - half_side * plane[2]) + (half_side * c[2]);
	// right bottom
	vertices[1][0] = (sq->coords[0] - half_side * plane[0]) - (half_side * c[0]);
	vertices[1][1] = (sq->coords[1] - half_side * plane[1]) - (half_side * c[1]);
	vertices[1][2] = (sq->coords[2] - half_side * plane[2]) - (half_side * c[2]);
	// right top
	vertices[2][0] = (sq->coords[0] + half_side * plane[0]) - (half_side * c[0]);
	vertices[2][1] = (sq->coords[1] + half_side * plane[1]) - (half_side * c[1]);
	vertices[2][2] = (sq->coords[2] + half_side * plane[2]) - (half_side * c[2]);
	// left top
	vertices[3][0] = (sq->coords[0] + half_side * plane[0]) + (half_side * c[0]);
	vertices[3][1] = (sq->coords[1] + half_side * plane[1]) + (half_side * c[1]);
	vertices[3][2] = (sq->coords[2] + half_side * plane[2]) + (half_side * c[2]);
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 2; j++)
			printf("v[%d][%d] = %f\n", i, j, vertices[i][j]);
		printf("\n");
	}
	free(plane);
	free(c);
	return (vertices);
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
	get_vertices(scene->obj_lst->obj);
	//draw_square(scene->obj_lst->obj, scene, &img);
	//free(scene->amb->colors);
	//free(scene->amb);
	//free(scene->cam);
	//free(scene->obj_lst->obj);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}