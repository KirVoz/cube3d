/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:43:08 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/15 17:22:28 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "init.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	mouse_move(int x, int y, t_data *data)
{
	int	prevX;
	int	prevY;

	prevX = WIDTH / 2;
	prevY = HEIGHT / 2;
	data->mouse.rotSpeed = (x - prevX) * data->mouse.sense;
	data->mouse.oldDirX = data->dirX;
	data->dirX = data->dirX * cos(-data->mouse.rotSpeed) - data->dirY
		* sin(-data->mouse.rotSpeed);
	data->dirY = data->mouse.oldDirX * sin(-data->mouse.rotSpeed) + data->dirY
		* cos(-data->mouse.rotSpeed);
	data->mouse.oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(-data->mouse.rotSpeed) - data->planeY
		* sin(-data->mouse.rotSpeed);
	data->planeY = data->mouse.oldPlaneX * sin(-data->mouse.rotSpeed)
		+ data->planeY * cos(-data->mouse.rotSpeed);
	data->pitch = y - prevY;
	mlx_mouse_move(data->win, WIDTH / 2, HEIGHT / 2);
	prevX = WIDTH / 2;
	prevY = HEIGHT / 2;
	return (0);
}

int	close_cub(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 17, close_cub, data);
	if (__LINUX__)
		mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
}

static t_data	*exit_free(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map1[i])
		free(data->map1[i++]);
	free(data->map1);
	free(data);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_val	*val;

	printf("MAIN\n");
	if (argc == 2)
	{
		val = (t_val *)s_alloc(1, sizeof(t_val));
		parser_main(val, argv);
		data = (t_data *)s_alloc(1, sizeof(t_data));
		data_init(val, data);
		data = exit_free(data);
	}
	else
		exit_fail("Pass a map with .cub extension");
	return (0);
}
