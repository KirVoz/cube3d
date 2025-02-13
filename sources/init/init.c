/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:43 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/13 21:43:36 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	data_init(t_val *val, t_data *data);
static void	position_init(t_data *data, t_val *val);
static void	map_init(t_data *data, t_val *val);
static void	hooks_init(t_data *data);

void	init_main(char **argv, t_data *data)
{
	t_val	*val;

	val = (t_val *)s_alloc(1, sizeof(t_val));
	data = (t_data *)s_alloc(1, sizeof(t_data));
	parser_main(val, argv);
	data_init(val, data);
}

static void	data_init(t_val *val, t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	textures_init(data, val);
	position_init(data, val);
	map_init(data, val);
	// size_t	i = 0, j = 0;
	// while (i < data->map_height)
	// {
	// 	while (j < data->map_width)
	// 	{
	// 		printf("%d", data->map1[i][j]);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	i++;
	// 	printf("\n");
	// }
	hooks_init(data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}

static void	hooks_init(t_data *data)
{
	data->keys = (t_keys *)s_alloc(1, sizeof(t_keys));
	data->mouse = (t_mouse *)s_alloc(1, sizeof(t_mouse));
	data->keys->w = 0;
	data->keys->a = 0;
	data->keys->s = 0;
	data->keys->d = 0;
	data->keys->left = 0;
	data->keys->right = 0;
	data->keys->moveSpeed = 0.05;
	data->mouse->rotSpeed = 1.5 * (PI / 180);
	data->pitch = 0;
	hooks(data);
}

static void	map_size(t_data *data, t_val *val)
{
	size_t	i;
	size_t	j;

	i = val->map_first_i;
	j = 0;
	data->map_height = 0;
	data->map_width = 0;
	while (val->mapv[i])
	{
		while (val->mapv[i][j])
			j++;
		if (j > data->map_width)
			data->map_width = j;
		j = 0;
		i++;
	}
	data->map_height = i - val->map_first_i;
}

static void	map_alloc(t_data *data)
{
	size_t	i;

	i = 0;
	data->map1 = (int **)s_alloc(data->map_height, sizeof(int *));
	while (i < data->map_height)
	{
		data->map1[i] = (int *)s_alloc(data->map_width, sizeof(int));
		i++;
	}
}

static void	map_init(t_data *data, t_val *val)
{
	size_t	i;
	size_t	j;

	i = val->map_first_i;
	j = 0;
	map_size(data, val);
	map_alloc(data);
	while (val->mapv[i])
	{
		while (val->mapv[i][j])
		{
			if (val->mapv[i][j] == '1')
				data->map1[i - val->map_first_i][j] = 1;
			else if (val->mapv[i][j] == '0' || val->mapv[i][j] == 'N'
					|| val->mapv[i][j] == 'S' || val->mapv[i][j] == 'W'
					|| val->mapv[i][j] == 'E')
				data->map1[i - val->map_first_i][j] = 0;
			else
				data->map1[i - val->map_first_i][j] = 2;
			j++;
		}
		j = 0;
		i++;
		}
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
