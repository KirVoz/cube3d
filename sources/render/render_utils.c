/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:02:50 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 18:02:53 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ray->raydir_x > 0)
			ray->hit_side = 'E';
		else
			ray->hit_side = 'W';
	}
	else
	{
		if (ray->raydir_y > 0)
			ray->hit_side = 'S';
		else
			ray->hit_side = 'N';
	}
}

void	init_ray(t_data *data, t_ray *ray)
{
	ray->cam_x = 2 * ray->x / (double)WIDTH - 1;
	ray->raydir_x = data->dir_x + data->plane_x * ray->cam_x;
	ray->raydir_y = data->dir_y + data->plane_y * ray->cam_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (ray->raydir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

void	init_ray2(t_data *data, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_dist_y;
	}
}
