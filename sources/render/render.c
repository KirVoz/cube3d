#include "../includes/cub3d.h"

static void	init_ray(t_data *data, t_ray *ray)
{
	ray->cameraX = 2 * ray->x / (double)SCENE_AREA_WIDTH - 1; // camera angle
	ray->rayDirX = data->dirX + data->planeX * ray->cameraX;  // ray directions
	ray->rayDirY = data->dirY + data->planeY * ray->cameraX;
	ray->mapX = (int)data->posX; // current map squares
	ray->mapY = (int)data->posY;
	if (ray->rayDirX == 0) // is ray parallel to the axis
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

static void	init_ray2(t_data *data, t_ray *ray)
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

static void	what_side(t_ray *ray)
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

static void	ray_hit(t_data *data, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if ((*data->map1)[ray->mapY][ray->mapX] > 0)
		{
			ray->hit = 1;
			what_side(ray);
		}
	}
}

static void	perpWallDist(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - data->posX + (1 - ray->stepX) / 2.0)
			/ ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - data->posY + (1 - ray->stepY) / 2.0)
			/ ray->rayDirY;
}

static void	line_height(t_ray *ray)
{
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

static void	what_texture(t_texture **t, t_ray ray, t_data *data)
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

void	draw_scene(t_data *data)
{
	t_ray		ray;
	t_texture	*t;
	double		wallX;
	int			texX;
	int			d;
	int			texY;
	int			color;

	ray.x = 0;
	while (ray.x < SCENE_AREA_WIDTH)
	{
		init_ray(data, &ray);
		init_ray2(data, &ray);
		ray_hit(data, &ray);
		perpWallDist(data, &ray);
		line_height(&ray);
		what_texture(&t, ray, data);
		if (ray.side == 0)
			wallX = data->posY + ray.perpWallDist * ray.rayDirY;
		else
			wallX = data->posX + ray.perpWallDist * ray.rayDirX;
		wallX -= floor(wallX);
		texX = (int)(wallX * (double)(t->width));
		if (ray.side == 0 && ray.rayDirX > 0)
			texX = t->width - texX - 1;
		if (ray.side == 1 && ray.rayDirY < 0)
			texX = t->width - texX - 1;
		ray.y = ray.drawStart;
		while (ray.y < ray.drawEnd)
		{
			d = ray.y * 256 - HEIGHT * 128 + ray.lineHeight * 128;
			texY = ((d * t->height) / ray.lineHeight) / 256;
			color = *(int *)(t->addr + (texY * t->line_length + texX * (t->bpp
							/ 8)));
			my_mlx_pixel_put(data, ray.x, ray.y, color);
			ray.y++;
		}
		ray.x++;
	}
}
