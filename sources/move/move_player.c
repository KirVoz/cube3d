#include "cub3d.h"

void	move_forward(t_data *data, double moveSpeed)
{
	double	newPosX;
	double	newPosY;

	newPosX = data->posX + data->dirX * moveSpeed;
	newPosY = data->posY + data->dirY * moveSpeed;
	if (newPosX >= 0 && newPosX < data->map_width && newPosY >= 0
		&& newPosY < data->map_height && !check_collision(data, newPosX,
			newPosY))
	{
		data->posX = newPosX;
		data->posY = newPosY;
	}
}

void	move_backward(t_data *data, double moveSpeed)
{
	double	newPosX;
	double	newPosY;

	newPosX = data->posX - data->dirX * moveSpeed;
	newPosY = data->posY - data->dirY * moveSpeed;
	if (newPosX >= 0 && newPosX < data->map_width && newPosY >= 0
		&& newPosY < data->map_height && !check_collision(data, newPosX,
			newPosY))
	{
		data->posX = newPosX;
		data->posY = newPosY;
	}
}

void	move_left(t_data *data, double moveSpeed)
{
	double	newPosX;
	double	newPosY;

	newPosX = data->posX - data->planeX * moveSpeed;
	newPosY = data->posY - data->planeY * moveSpeed;
	if (newPosX >= 0 && newPosX < data->map_width && newPosY >= 0
		&& newPosY < data->map_height && !check_collision(data, newPosX,
			newPosY))
	{
		data->posX = newPosX;
		data->posY = newPosY;
	}
}

void	move_right(t_data *data, double moveSpeed)
{
	double	newPosX;
	double	newPosY;

	newPosX = data->posX + data->planeX * moveSpeed;
	newPosY = data->posY + data->planeY * moveSpeed;
	if (newPosX >= 0 && newPosX < data->map_width && newPosY >= 0
		&& newPosY < data->map_height && !check_collision(data, newPosX,
			newPosY))
	{
		data->posX = newPosX;
		data->posY = newPosY;
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
