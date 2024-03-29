#include "../../includes/minirt.h"

static void		set_current_params(double point[3], t_plane *plane,
					   t_params *current)
{
	current->colors = plane->colors;
	current->point = point;
	current->normal = malloc(sizeof(double) * 3);
	if (current->normal == NULL)
		exit_error("Malloc failed");
	ft_memcpy(current->normal, plane->vector, sizeof(double) * 3);
}

static void		set_c_o(double c_o[3], double coords[3], double origin[3])
{
	c_o[0] = coords[0] - origin[0];
	c_o[1] = coords[1] - origin[1];
	c_o[2] = coords[2] - origin[2];
}

double			intersect_plane(void *obj, double ray[3],
					t_params *current, double origin[3])
{
	t_plane		*plane;
	double		denom;
	double		c_o[3];
	double		t;

	plane = (t_plane *)obj;
	denom = dot(plane->vector, ray);
	if (fabs(denom) <= 0.000001)
		return (0);
	set_c_o(c_o, plane->coords, origin);
	t = dot(c_o, plane->vector) / denom;
	if (t < 0)
		return (0);
	if (current != NULL)
		set_current_params(get_point(origin, ray, t), plane, current);
	return (t);
}
