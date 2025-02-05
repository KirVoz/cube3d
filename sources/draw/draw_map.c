#include "../includes/cub3d.h"

void draw_map(t_data *data)
{
    int y, x, i, j, color;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            color = ((*data->map1)[y][x] == 1) ? 0xFFFFFF : 0x000000;

            for (i = 0; i < TILE_SIZE; i++)
            {
                for (j = 0; j < TILE_SIZE; j++)
                {
                    if (i == 0 || j == 0 || i == TILE_SIZE - 1 || j == TILE_SIZE - 1)
						my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, 0xFF0000);
					else if ((*data->map1)[y][x] == 1)
						my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
                }
            }
        }
    }
}

void fill_floor(t_data *data, int color)
{
    int x;
    int y;

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

void fill_sealing(t_data *data, int color)
{
    int x;
    int y;

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
