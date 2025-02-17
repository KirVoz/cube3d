#include "cub3d.h"

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
		if (data->map1[ray->mapY][ray->mapX] > 0)
		{
			ray->hit = 1;
			what_side(ray);
		}
	}
}

static void	perp_wall_dist(t_data *data, t_ray *ray)
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

void	draw_texture(t_data *data, t_ray *ray, t_texture *t)
{
	t_draw_texture	draw;

	if (ray->side == 0)
		draw.hit = data->posY + ray->perpWallDist * ray->rayDirY;
	else
		draw.hit = data->posX + ray->perpWallDist * ray->rayDirX;
	draw.hit -= floor(draw.hit);
	draw.tex_x = (int)(draw.hit * (double)(t->width));
	if (ray->side == 0 && ray->rayDirX > 0)
		draw.tex_x = t->width - draw.tex_x - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		draw.tex_x = t->width - draw.tex_x - 1;
	ray->y = ray->drawStart;
	while (ray->y < ray->drawEnd)
	{
		draw.d = ray->y * 256 - HEIGHT * 128 + ray->lineHeight * 128;
		draw.tex_y = ((draw.d * t->height) / ray->lineHeight) / 256;
		draw.color = *(int *)(t->addr + (draw.tex_y * t->line_length
					+ draw.tex_x * (t->bpp / 8)));
		my_mlx_pixel_put(data, ray->x, ray->y, draw.color);
		ray->y++;
	}
}

void	draw_scene(t_data *data)
{
	t_ray		ray;
	t_texture	*t;

	ray.x = 0;
	while (ray.x < WIDTH)
	{
		init_ray(data, &ray);
		init_ray2(data, &ray);
		ray_hit(data, &ray);
		perp_wall_dist(data, &ray);
		line_height(&ray);
		if (data->map1[ray.mapY][ray.mapX] == 3) // Check if it's a door
			draw_door(data, ray);
		else
		{
			what_texture(&t, ray, data);
			draw_texture(data, &ray, t);
		}
		ray.x++;
	}
}
