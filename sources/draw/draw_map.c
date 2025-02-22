/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:00:38 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 18:00:40 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_draw_map(t_data *data, t_draw_map *cord)
{
	cord->start_x = (int)data->pos_x - MINIMAP_SIZE_W / 2;
	cord->start_y = (int)data->pos_y - MINIMAP_SIZE_H / 2;
	cord->end_x = cord->start_x + MINIMAP_SIZE_W;
	cord->end_y = cord->start_y + MINIMAP_SIZE_H;
	cord->y = cord->start_y;
}

static void	draw_tile_with_border(t_data *data, int x, int y, int color)
{
	draw_tile_border(data, x, y);
	draw_tile(data, x, y, color);
}

static int	get_tile_color(int tile_value)
{
	if (tile_value == 0)
		return (0xFFFFFF);
	if (tile_value == 1)
		return (0xFF0000);
	if (tile_value == 2)
		return (0xFFFF00);
	if (tile_value == 3)
		return (0x00FF00);
	return (0x000000);
}

void	draw_map(t_data *data)
{
	t_draw_map	cord;
	int			color;

	init_draw_map(data, &cord);
	while (cord.y < cord.end_y)
	{
		cord.x = cord.start_x;
		while (cord.x < cord.end_x)
		{
			if (cord.x >= 0 && cord.x < (int)data->map_width && cord.y >= 0
				&& cord.y < (int)data->map_height)
			{
				color = get_tile_color(data->map1[cord.y][cord.x]);
				draw_tile_with_border(data, cord.x - cord.start_x, cord.y
					- cord.start_y, color);
			}
			cord.x++;
		}
		cord.y++;
	}
}
