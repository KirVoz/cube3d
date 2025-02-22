/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:00:57 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 18:00:58 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_floor(t_data *data, int color)
{
	int	x;
	int	y;

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

void	fill_ceiling(t_data *data, int color)
{
	int	x;
	int	y;

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

void	fill_map(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINIMAP_SIZE_W * TILE_SIZE)
	{
		y = 0;
		while (y < MINIMAP_SIZE_H * TILE_SIZE)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_tile_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			if (i == 0 || j == 0 || i == TILE_SIZE - 0.5 || j == TILE_SIZE
				- 0.5)
				my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i,
					0x000000);
		}
	}
}

void	draw_tile(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (++i < TILE_SIZE - 1)
	{
		j = 0;
		while (++j < TILE_SIZE - 1)
			my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
	}
}
