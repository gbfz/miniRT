#include "../../includes/minirt.h"

void	set_triangle_params(double point[3], double normal[3],
			    t_tri *tri, t_params *current)
{
	current->id = 4;
	current->colors = tri->colors;
	current->point = point;
	current->normal = normal;
}

void	set_vectors_to_null(double *vec[3])
{
	vec[PVEC] = NULL;
	vec[TVEC] = NULL;
	vec[QVEC] = NULL;
}

double	free_vectors(double *vec[3])
{
	free(vec[0]);
	free(vec[1]);
	free(vec[2]);
	return (0);
}

void	free_edges(double *edge[2])
{
	free(edge[0]);
	free(edge[1]);
}
