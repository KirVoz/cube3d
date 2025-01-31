#include "../includes/cube3d.h"

void perform_dda(t_data *data, double rayDirX, double rayDirY, int *mapX, int *mapY, int *side)
{
    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;
    
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    double sideDistX = (rayDirX < 0) ? (data->posX - *mapX) * deltaDistX : (*mapX + 1.0 - data->posX) * deltaDistX;
    double sideDistY = (rayDirY < 0) ? (data->posY - *mapY) * deltaDistY : (*mapY + 1.0 - data->posY) * deltaDistY;

    while (data->map1[*mapY][*mapX] == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }
    }
}