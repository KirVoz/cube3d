#include "../includes/cub3d.h"

void	move_forward(t_data *data, double moveSpeed)
{
	double	newPosX;
	double	newPosY;

	newPosX = data->posX + data->dirX * moveSpeed;
	newPosY = data->posY + data->dirY * moveSpeed;
	if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0
		&& newPosY < MAP_HEIGHT
		&& (*data->map1)[(int)newPosY][(int)newPosX] == 0)
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
	if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0
		&& newPosY < MAP_HEIGHT
		&& (*data->map1)[(int)newPosY][(int)newPosX] == 0)
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
	if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0
		&& newPosY < MAP_HEIGHT
		&& (*data->map1)[(int)newPosY][(int)newPosX] == 0)
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
	if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0
		&& newPosY < MAP_HEIGHT
		&& (*data->map1)[(int)newPosY][(int)newPosX] == 0)
	{
		data->posX = newPosX;
		data->posY = newPosY;
	}
}

void	move_player(t_data *data)
{
	double	moveSpeed;

	moveSpeed = 0.05;
	if (data->keys->w)
		move_forward(data, moveSpeed);
	if (data->keys->s)
		move_backward(data, moveSpeed);
	if (data->keys->a)
		move_left(data, moveSpeed);
	if (data->keys->d)
		move_right(data, moveSpeed);
	if (data->keys->left)
		rotate_left(data, data->mouse->rotSpeed);
	if (data->keys->right)
		rotate_right(data, data->mouse->rotSpeed);
}
