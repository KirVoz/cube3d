#include "../includes/cub3d.h"

void draw_scene(t_data *data)
{
    int x;
    for (x = 0; x < SCENE_AREA_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCENE_AREA_WIDTH - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double sideDistX;
        double sideDistY;
        int stepX;
        int stepY;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }

        int hit = 0;
        int side;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if ((*data->map1)[mapY][mapX] > 0)
                hit = 1;
        }

        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - data->posX + (1 - stepX) / 2.0) / rayDirX;
        else
            perpWallDist = (mapY - data->posY + (1 - stepY) / 2.0) / rayDirY;

        int lineHeight = (int)(HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        int color;
        switch ((*data->map1)[mapY][mapX])
        {
            case 1: color = 0xFF0000; break;
            case 2: color = 0x00FF00; break;
            case 3: color = 0x0000FF; break;
            case 4: color = 0xFFFFFF; break;
            default: color = 0xFFFF00; break;
        }
        if (side == 1)
            color = color / 2;

        int y;
        for (y = drawStart; y < drawEnd; y++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}
