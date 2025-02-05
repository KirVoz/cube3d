#include "../includes/cub3d.h"

void	rotate_left(t_data *data, double rotSpeed)
{
	data->oldDirX = data->dirX;
	data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
	data->dirY = data->oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
	data->oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
	data->planeY = data->oldPlaneX * sin(rotSpeed) + data->planeY
		* cos(rotSpeed);
}

void	rotate_right(t_data *data, double rotSpeed)
{
	data->oldDirX = data->dirX;
	data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
	data->dirY = data->oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
	data->oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(-rotSpeed) - data->planeY
		* sin(-rotSpeed);
	data->planeY = data->oldPlaneX * sin(-rotSpeed) + data->planeY
		* cos(-rotSpeed);
}
