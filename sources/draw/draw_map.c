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

// void	draw_map(t_data *data)
// {
// 	int	y;
// 	int	x;
// 	int	color;

// 	y = 0;
// 	while (y < 10)
// 	{
// 		x = 0;
// 		while (x < 10)
// 		{
// 			if (data->map1[y][x] == 1)
// 				color = 0xFFFFFF;
// 			draw_tile_border(data, x, y);
// 			if (data->map1[y][x] == 1)
// 				draw_tile(data, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	draw_map(t_data *data)
{
    int	y;
    int	x;
    int	color;
    int	start_x;
    int	start_y;
    int	end_x;
    int	end_y;

    start_x = (int)data->posX - MINIMAP_SIZE / 2;
    start_y = (int)data->posY - MINIMAP_SIZE / 2;
    end_x = start_x + MINIMAP_SIZE;
    end_y = start_y + MINIMAP_SIZE;

    y = start_y;
    while (y < end_y)
    {
        x = start_x;
        while (x < end_x)
        {
            if (x >= 0 && x < (int)data->map_width && y >= 0 && y < (int)data->map_height)
            {
                if (data->map1[y][x] == 1)
                    color = 0xFFFFFF;
                else
                    color = 0x000000;
                draw_tile_border(data, x - start_x, y - start_y);
                if (data->map1[y][x] == 1)
                    draw_tile(data, x - start_x, y - start_y, color);
            }
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
	while (x < 10 * TILE_SIZE)
	{
		y = 0;
		while (y < 10 * TILE_SIZE)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}
