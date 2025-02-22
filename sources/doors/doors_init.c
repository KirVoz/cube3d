/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:59:53 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 18:00:17 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_doors(t_data *data)
{
	int	i;
	int	j;

	data->num_doors = 0;
	i = -1;
	while (++i < (int)data->map_height)
	{
		j = -1;
		while (++j < (int)data->map_width)
		{
			if (data->map1[i][j] == 3)
				data->num_doors++;
		}
	}
}

static void	init_door_tex(t_data *data, t_doors_tex *tex)
{
	tex->t[0].img = mlx_xpm_file_to_image(data->mlx, "./textures/close.xpm",
			&tex->t[0].width, &tex->t[0].height);
	tex->t[1].img = mlx_xpm_file_to_image(data->mlx, "./textures/opening.xpm",
			&tex->t[1].width, &tex->t[1].height);
	tex->t[2].img = mlx_xpm_file_to_image(data->mlx, "./textures/closing.xpm",
			&tex->t[2].width, &tex->t[2].height);
	tex->t[3].img = mlx_xpm_file_to_image(data->mlx, "./textures/open.xpm",
			&tex->t[3].width, &tex->t[3].height);
	if (!tex->t[0].img || !tex->t[1].img || !tex->t[2].img || !tex->t[3].img)
		exit_fail("Failed to load door textures");
	tex->t[0].addr = mlx_get_data_addr(tex->t[0].img, &tex->t[0].bpp,
			&tex->t[0].line_length, &tex->t[0].endian);
	tex->t[1].addr = mlx_get_data_addr(tex->t[1].img, &tex->t[1].bpp,
			&tex->t[1].line_length, &tex->t[1].endian);
	tex->t[2].addr = mlx_get_data_addr(tex->t[2].img, &tex->t[2].bpp,
			&tex->t[2].line_length, &tex->t[2].endian);
	tex->t[3].addr = mlx_get_data_addr(tex->t[3].img, &tex->t[3].bpp,
			&tex->t[3].line_length, &tex->t[3].endian);
	if (!tex->t[0].addr || !tex->t[1].addr || !tex->t[2].addr
		|| !tex->t[3].addr)
		exit_fail("Failed to get door texture data address");
}

static void	door_init2(t_data *data)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (++i < (int)data->map_height)
	{
		j = -1;
		while (++j < (int)data->map_width)
		{
			if (data->map1[i][j] == 3)
			{
				data->door[k].x = j;
				data->door[k].y = i;
				data->door[k].state = DOOR_CLOSED;
				data->door[k].anim_progress = 0.0f;
				k++;
			}
		}
	}
}

void	door_init(t_data *data)
{
	t_doors_tex	tex;

	init_door_tex(data, &tex);
	data->tex = tex;
	count_doors(data);
	data->door = (t_door *)malloc(data->num_doors * sizeof(t_door));
	if (!data->door)
		exit_fail("Failed to allocate memory for doors");
	door_init2(data);
}
