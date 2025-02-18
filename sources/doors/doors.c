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
		int frame = (int)(data->door[i].anim_progress * 4);
		if (frame > 3)
			frame = 3;
		data->door[i].t = data->tex.t[frame];
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

	player_x = (int)data->posX;
	player_y = (int)data->posY;
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

int	check_door(t_data *data, int posx, int posy)
{
	int	i;

	i = 0;
	if (data->map1[posy][posx] == 3)
	{
		while (i <= data->num_doors)
		{
			if (data->door[i].x == posx && data->door[i].y == posy)
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

	door_index = -1;
	for (int i = 0; i < data->num_doors; i++)
	{
		if (data->door[i].x == ray.mapX && data->door[i].y == ray.mapY)
		{
			door_index = i;
			break ;
		}
	}
	if (door_index != -1)
	{
		draw_texture(data, &ray, &data->door[door_index].t);
	}
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

static void	init_door_tex(t_data *data, t_doors_tex *tex)
{
	tex->t[0].img = mlx_xpm_file_to_image(data->mlx, "./textures/close.xpm",
			&tex->t[0].width, &tex->t[0].height);
	tex->t[1].img = mlx_xpm_file_to_image(data->mlx, "./textures/opening.xpm",
			&tex->t[1].width, &tex->t[1].height);
	tex->t[2].img = mlx_xpm_file_to_image(data->mlx, "./textures/closing.xpm",
			&tex->t[2].width, &tex->t[2].height);
	tex->t[3].img = mlx_xpm_file_to_image(data->mlx, "./textures/open.xpm",
			&tex->t[3].width, &tex->t[3].height);
	if (!tex->t[0].img || !tex->t[1].img || !tex->t[2].img || !tex->t[3].img)
		exit_fail("Failed to load door textures");
	tex->t[0].addr = mlx_get_data_addr(tex->t[0].img, &tex->t[0].bpp,
			&tex->t[0].line_length, &tex->t[0].endian);
	tex->t[1].addr = mlx_get_data_addr(tex->t[1].img, &tex->t[1].bpp,
			&tex->t[1].line_length, &tex->t[1].endian);
	tex->t[2].addr = mlx_get_data_addr(tex->t[2].img, &tex->t[2].bpp,
			&tex->t[2].line_length, &tex->t[2].endian);
	tex->t[3].addr = mlx_get_data_addr(tex->t[3].img, &tex->t[3].bpp,
			&tex->t[3].line_length, &tex->t[3].endian);
	if (!tex->t[0].addr || !tex->t[1].addr || !tex->t[2].addr
		|| !tex->t[3].addr)
		exit_fail("Failed to get door texture data address");
}

static void	door_init2(t_data *data)
{
	int	i;
	int	j;
	int	k;

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
				k++;
			}
		}
	}
}

void	door_init(t_data *data)
{
	t_doors_tex	tex;

	init_door_tex(data, &tex);
	data->tex = tex;
	count_doors(data);
	data->door = (t_door *)malloc(data->num_doors * sizeof(t_door));
	if (!data->door)
		exit_fail("Failed to allocate memory for doors");
	door_init2(data);
}
