#include "cub3d.h"

void	rotate_left_right(t_data *data, double rot_speed)
{
	data->mouse.old_d_x = data->dir_x;
	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = data->mouse.old_d_x * sin(rot_speed) + data->dir_y
		* cos(rot_speed);
	data->mouse.old_pl_x = data->plane_x;
	data->plane_x = data->plane_x * cos(rot_speed) - data->plane_y
		* sin(rot_speed);
	data->plane_y = data->mouse.old_pl_x * sin(rot_speed) + data->plane_y
		* cos(rot_speed);
}

int	check_door_collision(t_data *data, double x, double y)
{
	int	i;

	i = -1;
	while (++i < data->num_doors)
	{
		if ((data->door[i].x == (int)x && data->door[i].y == (int)y)
			|| (data->door[i].x == (int)(x + WALL_BUF)
			&& data->door[i].y == (int)y) || (data->door[i].x == (int)(x
			- WALL_BUF) && data->door[i].y == (int)y)
			|| (data->door[i].x == (int)x && data->door[i].y == (int)(y
			+ WALL_BUF)) || (data->door[i].x == (int)x
			&& data->door[i].y == (int)(y - WALL_BUF)))
		{
			if (data->door[i].state != DOOR_OPEN)
				return (1);
		}
	}
	return (0);
}

int	check_collision(t_data *data, double newpos_x, double newpos_y)
{
	if (newpos_x < 0 || newpos_x >= data->map_width || newpos_y < 0
		|| newpos_y >= data->map_height)
		return (1);
	if (data->map1[(int)(newpos_y)][(int)(newpos_x)] == 1
		|| data->map1[(int)(newpos_y)][(int)(newpos_x + WALL_BUF)] == 1
		|| data->map1[(int)(newpos_y)][(int)(newpos_x - WALL_BUF)] == 1
		|| data->map1[(int)(newpos_y + WALL_BUF)][(int)(newpos_x)] == 1
		|| data->map1[(int)(newpos_y - WALL_BUF)][(int)(newpos_x)] == 1)
		return (1);
	if (check_door_collision(data, newpos_x, newpos_y))
		return (1);
	return (0);
}
