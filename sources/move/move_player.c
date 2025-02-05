#include "../includes/cub3d.h"

void	move_player(t_data *data)
{
	double	moveSpeed;
	double  newPosX;
    double  newPosY;

	moveSpeed = 0.05;
	if (data->w)
	{
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
	if (data->s)
	{
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
	if (data->a)
	{
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
	if (data->d)
	{
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
	if (data->left)
	{
		data->oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY
			* sin(data->rotSpeed);
		data->dirY = data->oldDirX * sin(data->rotSpeed) + data->dirY
			* cos(data->rotSpeed);
		data->oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY
			* sin(data->rotSpeed);
		data->planeY = data->oldPlaneX * sin(data->rotSpeed) + data->planeY
			* cos(data->rotSpeed);
	}
	if (data->right)
	{
		data->oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY
			* sin(-data->rotSpeed);
		data->dirY = data->oldDirX * sin(-data->rotSpeed) + data->dirY
			* cos(-data->rotSpeed);
		data->oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY
			* sin(-data->rotSpeed);
		data->planeY = data->oldPlaneX * sin(-data->rotSpeed) + data->planeY
			* cos(-data->rotSpeed);
	}
}
