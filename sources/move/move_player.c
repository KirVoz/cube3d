#include "cub3d.h"

void	move_forward(t_data *data, double moveSpeed)
{
	double	newposx;
	double	newposy;

	newposx = data->posX + data->dirX * moveSpeed;
	newposy = data->posY + data->dirY * moveSpeed;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->posX = newposx;
		data->posY = newposy;
	}
}

void	move_backward(t_data *data, double moveSpeed)
{
	double	newposx;
	double	newposy;

	newposx = data->posX - data->dirX * moveSpeed;
	newposy = data->posY - data->dirY * moveSpeed;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->posX = newposx;
		data->posY = newposy;
	}
}

void	move_left(t_data *data, double moveSpeed)
{
	double	newposx;
	double	newposy;

	newposx = data->posX - data->planeX * moveSpeed;
	newposy = data->posY - data->planeY * moveSpeed;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->posX = newposx;
		data->posY = newposy;
	}
}

void	move_right(t_data *data, double moveSpeed)
{
	double	newposx;
	double	newposy;

	newposx = data->posX + data->planeX * moveSpeed;
	newposy = data->posY + data->planeY * moveSpeed;
	if (newposx >= 0 && newposx < data->map_width && newposy >= 0
		&& newposy < data->map_height && !check_collision(data, newposx,
			newposy))
	{
		data->posX = newposx;
		data->posY = newposy;
	}
}

void	move_player(t_data *data)
{
	if (data->keys.w)
		move_forward(data, data->keys.moveSpeed);
	if (data->keys.s)
		move_backward(data, data->keys.moveSpeed);
	if (data->keys.a)
		move_left(data, data->keys.moveSpeed);
	if (data->keys.d)
		move_right(data, data->keys.moveSpeed);
	if (data->keys.left)
		rotate_left_right(data, data->mouse.rotSpeed);
	if (data->keys.right)
		rotate_left_right(data, -data->mouse.rotSpeed);
}
