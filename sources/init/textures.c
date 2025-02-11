#include "../../includes/cub3d.h"

void	init_walls(t_data *data)
{
	data->wall = malloc(sizeof(char *) * 4);
	data->wall[0] = "./textures/wall_1.xpm";
	data->wall[1] = "./textures/wall_2.xpm";
	data->wall[2] = "./textures/wall_3.xpm";
	data->wall[3] = "./textures/wall_4.xpm";
}
void	textures_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->t[i].img = mlx_xpm_file_to_image(data->mlx, data->wall[i],
				&data->t[i].width, &data->t[i].height);
		data->t[i].addr = mlx_get_data_addr(data->t[i].img, &data->t[i].bpp,
				&data->t[i].line_length, &data->t[i].endian);
	}
}
