#include "cub3d.h"

void	rotate_left_right(t_data *data, double rotSpeed)
{
	data->mouse.oldDirX = data->dirX;
	data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
	data->dirY = data->mouse.oldDirX * sin(rotSpeed) + data->dirY
		* cos(rotSpeed);
	data->mouse.oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
	data->planeY = data->mouse.oldPlaneX * sin(rotSpeed) + data->planeY
		* cos(rotSpeed);
}

int	check_collision(t_data *data, double newPosX, double newPosY)
{
	if (newPosX < 0 || newPosX >= data->map_width || newPosY < 0
		|| newPosY >= data->map_height)
		return (1);
	if (data->map1[(int)(newPosY)][(int)(newPosX)] == 1
		|| data->map1[(int)(newPosY)][(int)(newPosX + WALL_BUF)] == 1
		|| data->map1[(int)(newPosY)][(int)(newPosX - WALL_BUF)] == 1
		|| data->map1[(int)(newPosY + WALL_BUF)][(int)(newPosX)] == 1
		|| data->map1[(int)(newPosY - WALL_BUF)][(int)(newPosX)] == 1)
		return (1);
	if ((data->map1[(int)(newPosY)][(int)(newPosX)] == 3
		|| data->map1[(int)(newPosY)][(int)(newPosX + WALL_BUF)] == 3
		|| data->map1[(int)(newPosY)][(int)(newPosX - WALL_BUF)] == 3
		|| data->map1[(int)(newPosY + WALL_BUF)][(int)(newPosX)] == 3
		|| data->map1[(int)(newPosY - WALL_BUF)][(int)(newPosX)] == 3)
		&& data->door->anim_progress == DOOR_CLOSED)
		return (1);
	return (0);
}
