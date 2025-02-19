/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:43:08 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/19 19:04:44 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "init.h"

static t_data	*exit_free(t_data *data);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	mouse_move(int x, int y, t_data *data)
{
	int	prev_x;
	int	prev_y;

	prev_x = WIDTH / 2;
	prev_y = HEIGHT / 2;
	data->mouse.rot_speed = (x - prev_x) * data->mouse.sense;
	data->mouse.old_d_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-data->mouse.rot_speed) - data->dir_y
		* sin(-data->mouse.rot_speed);
	data->dir_y = data->mouse.old_d_x * sin(-data->mouse.rot_speed) + data->dir_y
		* cos(-data->mouse.rot_speed);
	data->mouse.old_pl_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->mouse.rot_speed) - data->plane_y
		* sin(-data->mouse.rot_speed);
	data->plane_y = data->mouse.old_pl_x * sin(-data->mouse.rot_speed)
		+ data->plane_y * cos(-data->mouse.rot_speed);
	data->pitch = y - prev_y;
	mlx_mouse_move(data->win, WIDTH / 2, HEIGHT / 2);
	prev_x = WIDTH / 2;
	prev_y = HEIGHT / 2;
	return (0);
}

int	close_cub(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data = exit_free(data);
	// system("leaks cub3D");
	exit(0);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 17, close_cub, data);
	if (!LINUX)
		mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
}

static t_data	*exit_free(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->map_height)
		free(data->map1[i++]);
	if (data->num_doors > 0)
		free((void *)data->door);
	free(data->map1);
	free(data);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_val	*val;

	if (argc == 2)
	{
		val = (t_val *)s_alloc(1, sizeof(t_val));
		parser_main(val, argv);
		data = (t_data *)s_alloc(1, sizeof(t_data));
		data_init(val, data);
	}
	else
		exit_fail("Pass a map with .cub extension");
	return (0);
}
