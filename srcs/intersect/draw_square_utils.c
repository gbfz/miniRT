#include "../../includes/minirt.h"

double	get_orient(double p[3], double p1[3], double p2[3], double n[3])
{
	double o;
	double *c;
	double v1[3];
	double v2[3];

	v1[0] = p1[0] - p[0];
	v1[1] = p1[1] - p[1];
	v1[2] = p1[2] - p[2];
	v2[0] = p2[0] - p[0];
	v2[1] = p2[1] - p[1];
	v2[2] = p2[2] - p[2];
	c = cross(v1, v2);
	o = dot(c, n);
	free(c);
	return (o);
}
