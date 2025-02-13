#include "../includes/cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (keycode == 13 || keycode == 119)
		data->keys->w = 1;
	if (keycode == 0 || keycode == 97)
		data->keys->a = 1;
	if (keycode == 1 || keycode == 115)
		data->keys->s = 1;
	if (keycode == 2 || keycode == 100)
		data->keys->d = 1;
	if (keycode == 65363 || keycode == 123)
		data->keys->left = 1;
	if (keycode == 65361 || keycode == 124)
		data->keys->right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 119)
		data->keys->w = 0;
	if (keycode == 0 || keycode == 97)
		data->keys->a = 0;
	if (keycode == 1 || keycode == 115)
		data->keys->s = 0;
	if (keycode == 2 || keycode == 100)
		data->keys->d = 0;
	if (keycode == 65363 || keycode == 123)
		data->keys->left = 0;
	if (keycode == 65361 || keycode == 124)
		data->keys->right = 0;
	return (0);
}
