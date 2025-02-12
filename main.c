#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	mouse_move(int x, int y, t_data *data)
{
	int	prevX = WIDTH / 2;
	int	prevY = HEIGHT / 2;
	double		sense;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;

	sense = 0.01;
	rotSpeed = (x - prevX) * sense;
	oldDirX = data->dirX;
	data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
	data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
	oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(-rotSpeed) - data->planeY
		* sin(-rotSpeed);
	data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
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
	// mlx_hook(data->win, 6, 1L<<6, mouse_move, data); // macos
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc == 2)
		init_main(argv , data);
	exit_fail("Pass a map with .cub extension");

	return (0);
}
