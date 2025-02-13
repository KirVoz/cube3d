/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:53:01 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/13 17:31:34 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
