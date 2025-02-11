#include "../../includes/cub3d.h"

static void	draw_minimap(t_data *data)
{
	fill_map(data, 0x000000);
	draw_map(data);
	print_player(data, 0x00FF00);
	draw_viewing_angle(data, 0x888888);
}

int	render_next_frame(t_data *data)
{
	move_player(data);
	fill_sealing(data, 0x888888);
	fill_floor(data, 0x444444);
	draw_scene(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
