#include "../../includes/minirt.h"

int	key_hook(int key, t_data *data)
{
	if (key == 53)
		exit(0);
	if (key == 49)
	{
		data->img_lst = data->img_lst->next;
		if (data->img_lst == NULL)
			data->img_lst = data->lst_start;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_lst->img.img, 0, 0);
	return (0);
}

int	exit_hook(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	(void)data;
	exit(0);
}
