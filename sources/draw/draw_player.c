#include "../includes/cub3d.h"

void	draw_player_pixel(t_data *data, int x, int y, int color)
{
	my_mlx_pixel_put(data, (int)(data->posX * TILE_SIZE) + x, (int)(data->posY
			* TILE_SIZE) + y, color);
}

void	print_player(t_data *data, int color)
{
	int	player;
	int	x;
	int	y;

	player = 5;
	x = -player / 2;
	while (x < player / 2)
	{
		y = -player / 2;
		while (y < player / 2)
		{
			draw_player_pixel(data, x, y, color);
			y++;
		}
		x++;
	}
}
