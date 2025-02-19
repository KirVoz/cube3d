#include "cub3d.h"

void	move_forward(t_data *data, double ms)
{
	double	newposx;
	double	newposy;

	newposx = data->pos_x + data->dir_x * ms;
	newposy = data->pos_y + data->dir_y * ms;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->pos_x = newposx;
		data->pos_y = newposy;
	}
}

void	move_backward(t_data *data, double ms)
{
	double	newposx;
	double	newposy;

	newposx = data->pos_x - data->dir_x * ms;
	newposy = data->pos_y - data->dir_y * ms;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->pos_x = newposx;
		data->pos_y = newposy;
	}
}

void	move_left(t_data *data, double ms)
{
	double	newposx;
	double	newposy;

	newposx = data->pos_x - data->plane_x * ms;
	newposy = data->pos_y - data->plane_y * ms;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->pos_x = newposx;
		data->pos_y = newposy;
	}
}

void	move_right(t_data *data, double ms)
{
	double	newposx;
	double	newposy;

	newposx = data->pos_x + data->plane_x * ms;
	newposy = data->pos_y + data->plane_y * ms;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->pos_x = newposx;
		data->pos_y = newposy;
	}
}

void	move_player(t_data *data)
{
	if (data->keys.w)
		move_forward(data, data->keys.ms);
	if (data->keys.s)
		move_backward(data, data->keys.ms);
	if (data->keys.a)
		move_left(data, data->keys.ms);
	if (data->keys.d)
		move_right(data, data->keys.ms);
	if (data->keys.left)
		rotate_left_right(data, data->mouse.rot_speed);
	if (data->keys.right)
		rotate_left_right(data, -data->mouse.rot_speed);
}
