/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:51:39 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/16 16:32:31 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	map_size(t_data *data, t_val *val);
static void	map_alloc(t_data *data);

void	map_init(t_data *data, t_val *val)
{
	size_t	i;
	size_t	j;

	i = val->map_first_i;
	j = 0;
	map_size(data, val);
	map_alloc(data);
	while (i < data->map_height + val->map_first_i)
	{
		while (j < data->map_width)
		{
			if (val->mapv[i][j] == '1')
				data->map1[i - val->map_first_i][j] = 1;
			else if (val->mapv[i][j] == '0' || val->mapv[i][j] == 'N'
					|| val->mapv[i][j] == 'S' || val->mapv[i][j] == 'W'
					|| val->mapv[i][j] == 'E')
				data->map1[i - val->map_first_i][j] = 0;
			else if (val->mapv[i][j] == ' ' || j < data->map_width)
				data->map1[i - val->map_first_i][j] = 2;
			j++;
		}
		j = 0;
		i++;
	}
	data->map1[i] = NULL;
}

static void	map_size(t_data *data, t_val *val)
{
	size_t	i;
	size_t	j;

	i = val->map_first_i;
	j = 0;
	data->map_height = 0;
	data->map_width = 0;
	while (val->mapv[i])
	{
		while (val->mapv[i][j])
			j++;
		if (j > data->map_width)
			data->map_width = j;
		j = 0;
		i++;
	}
	data->map_height = i - val->map_first_i;
}

static void	map_alloc(t_data *data)
{
	size_t	i;

	i = 0;
	data->map1 = (int **)s_alloc(data->map_height, sizeof(int *));
	while (i < data->map_height)
	{
		data->map1[i] = (int *)s_alloc(data->map_width, sizeof(int));
		i++;
	}
}
