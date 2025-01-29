#include "cube3d.h"

int error_handler(char *error)
{
	ft_putstr_fd(error, 2);
	return (1);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (error_handler("Error\nInvalid number of arguments\n"));
	init(&data);
	if (!parser(av[1]))
	{
		proper_exit();
		return (error_handler("Error\nInvalid map\n"));
	}
	full_init(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
}
