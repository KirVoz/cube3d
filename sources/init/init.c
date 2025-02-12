/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:43 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/12 05:42:49 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	temp_init(t_data *data);
static void	data_init(t_val *val, t_data *data);
static void	position_init(t_data *data, t_val *val);
// static void	map_init(t_data *data, t_val *val);
static void hooks_init(t_data *data);

void	init_main(char **argv, t_data *data)
{
	t_val	*val;

	val = (t_val *)s_alloc(1, sizeof(t_val));
	data = (t_data *)s_alloc(1, sizeof(t_data));
	if (!ft_strncmp(argv[1], "temp", 4))
		temp_init(data);
	else
	{
		parser_main(val, argv);
		data_init(val, data);
	}
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
	// map_init(data, val);
	data->map1 = &map;
	hooks_init(data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}

static void hooks_init(t_data *data)
{
	data->w = 0;
	data->a = 0;
	data->s = 0;
	data->d = 0;
	data->left = 0;
	data->right = 0;
	data->pitch = 0;
	data->rotSpeed = 1 * (PI / 180);
	hooks(data);
}
// static void	map_init(t_data *data, t_val *val)
// {

// }

static void	position_init(t_data *data, t_val *val)
{
	data->posX = 4.5;
	data->posY = 7.5;
	if (val->map_v[val->starting_pos[0]][val->starting_pos[1]] == 'S')
	{
		data->dirX = 0;
		data->dirY = -1;
	}
	// screen direction are opposite to math direction (FUN FACT)
	data->planeX = -data->dirY * planeLen;
	data->planeY = data->dirX * planeLen;
}

static void	temp_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	init_walls(data);
	textures_init_temp(data);
	data->posX = 4.5;
	data->posY = 7.5;
	data->dirX = 0;
	data->dirY = -1;
	// screen direction are opposite to math direction (FUN FACT)
	data->planeX = -data->dirY * planeLen;
	data->planeY = data->dirX * planeLen;
	data->map1 = &map;
	data->w = 0;
	data->a = 0;
	data->s = 0;
	data->d = 0;
	data->left = 0;
	data->right = 0;
	data->pitch = 0;
	data->rotSpeed = 1 * (PI / 180);
	hooks(data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}
