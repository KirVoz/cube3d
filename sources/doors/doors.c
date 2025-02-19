#include "cub3d.h"

void	toggle_door(t_data *data, int x, int y)
{
	int	i;

	i = -1;
	while (++i < data->num_doors)
	{
		if (data->door[i].x == x && data->door[i].y == y)
		{
			if (data->door[i].state == DOOR_CLOSED)
			{
				data->door[i].state = DOOR_OPENING;
			}
			else if (data->door[i].state == DOOR_OPEN)
			{
				data->door[i].state = DOOR_CLOSING;
			}
			break ;
		}
	}
}

void	check_door_interaction(t_data *data)
{
	int	player_x;
	int	player_y;

	player_x = (int)data->pos_x;
	player_y = (int)data->pos_y;
	if (data->keys.door)
	{
		if (data->map1[player_y][player_x + 1] == 3)
			toggle_door(data, player_x + 1, player_y);
		else if (data->map1[player_y][player_x - 1] == 3)
			toggle_door(data, player_x - 1, player_y);
		else if (data->map1[player_y + 1][player_x] == 3)
			toggle_door(data, player_x, player_y + 1);
		else if (data->map1[player_y - 1][player_x] == 3)
			toggle_door(data, player_x, player_y - 1);
		data->keys.door = 0;
		data->keys.door_pressed = 0;
	}
}

int	check_door(t_data *data, int pos_x, int pos_y)
{
	int	i;

	i = 0;
	if (data->map1[pos_y][pos_x] == 3)
	{
		while (i <= data->num_doors)
		{
			if (data->door[i].x == pos_x && data->door[i].y == pos_y)
				break ;
		}
		if (data->door[i].state == DOOR_CLOSED)
			return (1);
	}
	return (0);
}

void	draw_door(t_data *data, t_ray ray)
{
	int	door_index;
	int	i;

	i = -1;
	door_index = -1;
	while (++i < data->num_doors)
	{
		if (data->door[i].x == ray.map_x && data->door[i].y == ray.map_y)
		{
			door_index = i;
			break ;
		}
	}
	if (door_index != -1)
		draw_texture(data, &ray, &data->door[door_index].t);
}
