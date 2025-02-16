#include "cub3d.h"

void	what_texture(t_texture **t, t_ray ray, t_data *data)
{
	if (ray.hit_side == 'N')
		*t = &data->t[0];
	else if (ray.hit_side == 'S')
		*t = &data->t[1];
	else if (ray.hit_side == 'E')
		*t = &data->t[2];
	else if (ray.hit_side == 'W')
		*t = &data->t[3];
}

void	what_side(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			ray->hit_side = 'E';
		else
			ray->hit_side = 'W';
	}
	else
	{
		if (ray->rayDirY > 0)
			ray->hit_side = 'S';
		else
			ray->hit_side = 'N';
	}
}

void	init_ray(t_data *data, t_ray *ray)
{
	ray->cameraX = 2 * ray->x / (double)WIDTH - 1;
	ray->rayDirX = data->dirX + data->planeX * ray->cameraX;
	ray->rayDirY = data->dirY + data->planeY * ray->cameraX;
	ray->mapX = (int)data->posX;
	ray->mapY = (int)data->posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

void	init_ray2(t_data *data, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - data->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - data->posY) * ray->deltaDistY;
	}
}
