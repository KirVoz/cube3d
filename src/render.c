#include "../includes/cube3d.h"

void raycast(t_data *data)
{
    for (int x = 0; x < WIDTH; x++)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->posX;
        int mapY = (int)data->posY;
        int side;

        perform_dda(data, rayDirX, rayDirY, &mapX, &mapY, &side);

        int color = (side == 0) ? 0xFFFFFF : 0xAAAAAA;
        for (int y = 0; y < HEIGHT; y++)
            my_mlx_pixel_put(data, x, y, color);
    }
}
