/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:53:01 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/12 18:11:00 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//del
void	init_walls(t_data *data)
{
	data->wall = malloc(sizeof(char *) * 4);
	data->wall[0] = "./textures/wall_1.xpm";
	data->wall[1] = "./textures/wall_2.xpm";
	data->wall[2] = "./textures/wall_3.xpm";
	data->wall[3] = "./textures/wall_4.xpm";
}

void	textures_init_temp(t_data *data)
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

void	textures_init(t_data *data, t_val *val)
{
	size_t	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->t[i].img = mlx_xpm_file_to_image(data->mlx, val->textures[i].path,
				&data->t[i].width, &data->t[i].height);
		data->t[i].addr = mlx_get_data_addr(data->t[i].img, &data->t[i].bpp,
				&data->t[i].line_length, &data->t[i].endian);
		i++;
	}
}