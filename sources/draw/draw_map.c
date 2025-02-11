#include "../includes/cub3d.h"

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
			if (i == 0 || j == 0 || i == TILE_SIZE - 0.5 || j == TILE_SIZE - 0.5)
				my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i,
					0xFF0000);
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

void	draw_map(t_data *data)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if ((*data->map1)[y][x] == 1)
				color = 0xFFFFFF;
			draw_tile_border(data, x, y);
			if ((*data->map1)[y][x] == 1)
				draw_tile(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	fill_floor(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	fill_sealing(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	fill_map(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < MAP_WIDTH * TILE_SIZE)
	{
		y = 0;
		while (y < MAP_HEIGHT * TILE_SIZE)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}
