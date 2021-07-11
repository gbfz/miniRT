#include "../../includes/minirt.h"

void	free_cam(t_cam *cam)
{
	free(cam->coords);
	free(cam->vector);
	free_matrix(cam->matrix);
	free(cam);
}
