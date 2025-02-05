#include "../../includes/cub3d.h"

int	render_next_frame(t_data *data)
{
	move_player(data);
	fill_sealing(data, 0x888888);
	fill_floor(data, 0x444444);
	draw_scene(data);
	draw_map(data);
	print_player(data, 0x00FF00);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
