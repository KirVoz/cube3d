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
	if (data->w)
		move_forward(data, moveSpeed);
	if (data->s)
		move_backward(data, moveSpeed);
	if (data->a)
		move_left(data, moveSpeed);
	if (data->d)
		move_right(data, moveSpeed);
	if (data->left)
		rotate_left(data, data->rotSpeed);
	if (data->right)
		rotate_right(data, data->rotSpeed);
}
