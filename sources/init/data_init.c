/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:43 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/17 09:39:10 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void		textures_colour_init(t_data *data, t_val *val);
static void		position_init(t_data *data, t_val *val);
static void		hooks_init(t_data *data);
static t_val	*free_val(t_val *val);

void	data_init(t_val *val, t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	textures_colour_init(data, val);
	position_init(data, val);
	map_init(data, val);
	size_t	i = 0, j = 0;
	while (i < data->map_height)
	{
		while (j < data->map_width)
		{
			printf("%d", data->map1[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
	hooks_init(data);
	val = free_val(val);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}

static void	textures_colour_init(t_data *data, t_val *val)
{
	size_t	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->t[i].img = mlx_xpm_file_to_image(data->mlx, val->textures[i].path,
				&data->t[i].width, &data->t[i].height);
		data->t[i].addr = mlx_get_data_addr(data->t[i].img, &data->t[i].bpp,
				&data->t[i].line_length, &data->t[i].endian);
		i++;
	}
	data->colours[C] = ((val->colours[C].rgb[0] << 16)
			| (val->colours[C].rgb[1] << 8)
			| val->colours[C].rgb[2]);
	data->colours[F] = ((val->colours[F].rgb[0] << 16)
			| (val->colours[F].rgb[1] << 8)
			| val->colours[F].rgb[2]);
}

static void	position_init(t_data *data, t_val *val)
{
	data->posX = val->starting_pos[0];
	data->posY = val->starting_pos[1];
	if (val->direction == 'S')
	{
		data->dirX = 0;
		data->dirY = 1;
	}
	else if (val->direction == 'N')
	{
		data->dirX = 0;
		data->dirY = -1;
	}
	else if (val->direction == 'W')
	{
		data->dirX = -1;
		data->dirY = 0;
	}
	else if (val->direction == 'E')
	{
		data->dirX = 1;
		data->dirY = 0;
	}
	data->planeX = -data->dirY * planeLen;
	data->planeY = data->dirX * planeLen;
}

static void	hooks_init(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.moveSpeed = 0.03;
	data->mouse.sense = 0.01;
	data->mouse.rotSpeed = 0.85 * (PI / 180);
	data->pitch = 0;
	hooks(data);
}

static t_val	*free_val(t_val *val)
{
	size_t	i;

	i = 0;
	while (val->mapv[i])
		free(val->mapv[i++]);
	free(val->mapv);
	while (val->tex_type < TEX_COUNT)
		free(val->textures[val->tex_type++].path);
	free(val);
	return (NULL);
}
