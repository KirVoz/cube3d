/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:43 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/22 18:04:51 by kvoznese         ###   ########.fr       */
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
	count_doors(data);
	if (data->num_doors > 0)
		door_init(data);
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
	data->pos_x = val->starting_pos[0];
	data->pos_y = val->starting_pos[1];
	if (val->direction == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (val->direction == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
	else if (val->direction == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
	else if (val->direction == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	data->plane_x = -data->dir_y * (FOV / 2 * PI / 180);
	data->plane_y = data->dir_x * (FOV / 2 * PI / 180);
}

static void	hooks_init(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.door = 0;
	data->keys.door_pressed = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.ms = 0.03;
	data->mouse.sense = 0.01;
	data->mouse.rot_speed = 0.85 * (PI / 180);
	data->pitch = 0;
	data->game_over = 0;
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
