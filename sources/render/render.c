/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:02:17 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 18:02:31 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_hit(t_data *data, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map1[ray->map_y][ray->map_x] > 0)
		{
			ray->hit = 1;
			what_side(ray);
		}
	}
}

static void	perp_wall_dist(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->pos_x + (1 - ray->step_x)
				/ 2.0) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->pos_y + (1 - ray->step_y)
				/ 2.0) / ray->raydir_y;
}

static void	line_height(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	draw_texture(t_data *data, t_ray *ray, t_texture *t)
{
	t_draw_texture	draw;

	if (ray->side == 0)
		draw.hit = data->pos_y + ray->perp_wall_dist * ray->raydir_y;
	else
		draw.hit = data->pos_x + ray->perp_wall_dist * ray->raydir_x;
	draw.hit -= floor(draw.hit);
	draw.tex_x = (int)(draw.hit * (double)(t->width));
	if (ray->side == 0 && ray->raydir_x > 0)
		draw.tex_x = t->width - draw.tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		draw.tex_x = t->width - draw.tex_x - 1;
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end)
	{
		draw.d = ray->y * 256 - HEIGHT * 128 + ray->line_height * 128;
		draw.tex_y = ((draw.d * t->height) / ray->line_height) / 256;
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
		if (data->map1[ray.map_y][ray.map_x] == 3)
			draw_door(data, ray);
		else
		{
			what_texture(&t, ray, data);
			draw_texture(data, &ray, t);
		}
		ray.x++;
	}
}
