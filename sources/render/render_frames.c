#include "../../includes/cub3d.h"

static void	draw_minimap(t_data *data)
{
	fill_map(data, 0x000000);
	draw_map(data);
	print_player(data, 0xFFFF00);
	draw_viewing_angle(data, 0x888888);
}

static void	end_game(t_data *data, char *message)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, 0x000000);
			y++;
		}
		x++;
	}
	mlx_string_put(data->mlx, data->win, WIDTH / 2, HEIGHT / 2, 0xFF0000,
		message);
}

int	render_next_frame(t_data *data)
{
	if (data->game_over)
	{
		mlx_clear_window(data->mlx, data->win);
		end_game(data, "YOU DIED");
	}
	else
	{
		if (data->map1[(int)data->posY][(int)data->posX] == 3)
			data->game_over = 1;
		else
			{
				check_door_interaction(data);
				door_animation(data);
				move_player(data);
				fill_ceiling(data, data->colours[C]);
				fill_floor(data, data->colours[F]);
				draw_scene(data);
				draw_minimap(data);
				mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
			}
	}
	return (0);
}
