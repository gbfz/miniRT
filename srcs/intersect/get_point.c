#include "../../includes/minirt.h"

double	*get_point(double origin[3], double ray[3], double t)
{
	double *point;

	point = malloc(sizeof(double) * 3);
	if (point == NULL)
		exit_error("Malloc failed");
	point[0] = origin[0] + ray[0] * t;
	point[1] = origin[1] + ray[1] * t;
	point[2] = origin[2] + ray[2] * t;
	return (point);
}
