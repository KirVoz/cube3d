#include "cub3d.h"

static void	draw_tile_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			if (i == 0 || j == 0 || i == TILE_SIZE - 0.5 || j == TILE_SIZE
				- 0.5)
				my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i,
					0x000000);
		}
	}
}

static void	draw_tile(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (++i < TILE_SIZE - 1)
	{
		j = 0;
		while (++j < TILE_SIZE - 1)
			my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
	}
}

static void	init_draw_map(t_data *data, t_draw_map *cord)
{
	cord->start_x = (int)data->posX - MINIMAP_SIZE_W / 2;
	cord->start_y = (int)data->posY - MINIMAP_SIZE_H / 2;
	cord->end_x = cord->start_x + MINIMAP_SIZE_W;
	cord->end_y = cord->start_y + MINIMAP_SIZE_H;
	cord->y = cord->start_y;
}

void	draw_map(t_data *data)
{
	t_draw_map	cord;

	init_draw_map(data, &cord);
	while (cord.y < cord.end_y)
	{
		cord.x = cord.start_x;
		while (cord.x < cord.end_x)
		{
			if (cord.x >= 0 && cord.x < (int)data->map_width && cord.y >= 0
				&& cord.y < (int)data->map_height)
			{
				draw_tile_border(data, cord.x - cord.start_x, cord.y
					- cord.start_y);
				if (data->map1[cord.y][cord.x] == 0)
					draw_tile(data, cord.x - cord.start_x, cord.y
						- cord.start_y, 0xFFFFFF);
				else if (data->map1[cord.y][cord.x] == 1)
					draw_tile(data, cord.x - cord.start_x, cord.y
						- cord.start_y, 0xFF0000);
				else if (data->map1[cord.y][cord.x] == 2)
					draw_tile(data, cord.x - cord.start_x, cord.y
						- cord.start_y, 0xFFFF00);
				else if (data->map1[cord.y][cord.x] == 3)
					draw_tile(data, cord.x - cord.start_x, cord.y
						- cord.start_y, 0x00FF00);
			}
			cord.x++;
		}
		cord.y++;
	}
}

void	fill_map(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINIMAP_SIZE_W * TILE_SIZE)
	{
		y = 0;
		while (y < MINIMAP_SIZE_H * TILE_SIZE)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}
