#include "../includes/cub3d.h"

void print_player(t_data *data, int color)
{
    int player = 5;
    int x, y;

    for (x = -player / 2; x < player / 2; x++)
    {
        for (y = -player / 2; y < player / 2; y++)
        {
            my_mlx_pixel_put(data, (int)(data->posX * TILE_SIZE) + x, (int)(data->posY * TILE_SIZE) + y, color);
        }
    }
}
