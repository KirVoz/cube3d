/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:43 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/07 13:40:27 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	temp_init(t_data *data);

void	init_main(char **argv, t_data *data)
{
	data = (t_data *)s_alloc(1, sizeof(t_data));
	(void)argv;
	// parser_main(argv, data);
	temp_init(data);
}

void	temp_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	init_walls(data);
	textures_init(data);
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
	data->rotSpeed = 1 * (M_PI / 180);
	hooks(data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}
