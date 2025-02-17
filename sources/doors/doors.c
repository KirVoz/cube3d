#include "cub3d.h"

void	door_animation(t_data *data)
{
	float	doors_anim_speed;

	doors_anim_speed = 0.01f;
	for (int i = 0; i < data->num_doors; i++)
	{
		if (data->door[i].state == DOOR_OPENING)
		{
			data->door[i].anim_progress += doors_anim_speed;
			if (data->door[i].anim_progress >= 1.0f)
			{
				data->door[i].anim_progress = 1.0f;
				data->door[i].state = DOOR_OPEN;
			}
		}
		else if (data->door[i].state == DOOR_CLOSING)
		{
			data->door[i].anim_progress -= doors_anim_speed;
			if (data->door[i].anim_progress <= 0.0f)
			{
				data->door[i].anim_progress = 0.0f;
				data->door[i].state = DOOR_CLOSED;
			}
		}
	}
}

void	toggle_door(t_data *data, int x, int y)
{
	for (int i = 0; i < data->num_doors; i++)
	{
		if (data->door[i].x == x && data->door[i].y == y)
		{
			if (data->door[i].state == DOOR_CLOSED)
			{
				
				data->door[i].state = DOOR_OPENING;
			}
			else if (data->door[i].state == DOOR_OPEN)
				data->door[i].state = DOOR_CLOSING;
			break ;
		}
	}
}

void	check_door_interaction(t_data *data)
{
	int	player_x;
	int	player_y;

	player_x = (int)data->posX;
	player_y = (int)data->posY;
	if (data->keys.door)
	{
		printf("door 0\n");
		if (data->map1[player_y][player_x + 1] == 3)
			toggle_door(data, player_x + 1, player_y);
		else if (data->map1[player_y][player_x - 1] == 3)
			toggle_door(data, player_x - 1, player_y);
		else if (data->map1[player_y + 1][player_x] == 3)
			toggle_door(data, player_x, player_y + 1);
		else if (data->map1[player_y - 1][player_x] == 3)
			toggle_door(data, player_x, player_y - 1);
		data->keys.door = 0;
	}
}

static void	load_d_texture(t_data *data, int i)
{
	data->door[i].t.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/wall_1.xpm", &data->door[i].t.width,
			&data->door[i].t.height);
	if (!data->door[i].t.img)
		exit_fail("Failed to load door texture");
	data->door[i].t.addr = mlx_get_data_addr(data->door[i].t.img,
			&data->door[i].t.bpp, &data->door[i].t.line_length,
			&data->door[i].t.endian);
}

void	draw_door(t_data *data, t_ray ray)
{

	if (ray.hit_side == 'N')
		draw_texture(data, &ray, &data->door[0].t);
	else if (ray.hit_side == 'S')
		draw_texture(data, &ray, &data->door[0].t);
	else if (ray.hit_side == 'E')
		draw_texture(data, &ray, &data->door[0].t);
	else if (ray.hit_side == 'W')
		draw_texture(data, &ray, &data->door[0].t);
}

void	count_doors(t_data *data)
{
	int	i;
	int	j;

	data->num_doors = 0;
	i = -1;
	while (++i < (int)data->map_height)
	{
		j = -1;
		while (++j < (int)data->map_width)
		{
			if (data->map1[i][j] == 3)
				data->num_doors++;
		}
	}
}
void	door_init(t_data *data)
{
	int	i;
	int	j;
	int	k;

	count_doors(data);
	data->door = (t_door *)malloc(data->num_doors * sizeof(t_door));
	if (!data->door)
		exit_fail("Failed to allocate memory for doors");
	k = 0;
	i = -1;
	while (++i < (int)data->map_height)
	{
		j = -1;
		while (++j < (int)data->map_width)
		{
			if (data->map1[i][j] == 3)
			{
				data->door[k].x = j;
				data->door[k].y = i;
				data->door[k].state = DOOR_CLOSED;
				data->door[k].anim_progress = 0.0f;
				load_d_texture(data, k);
				k++;
			}
		}
	}
}
