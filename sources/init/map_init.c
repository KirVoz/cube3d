/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:51:39 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/17 09:11:25 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	fill_row(t_data *data, t_val *val, size_t i);
static void	map_size(t_data *data, t_val *val);
static void	map_alloc(t_data *data);

void	map_init(t_data *data, t_val *val)
{
	size_t	i;

	i = val->map_first_i;
	map_size(data, val);
	map_alloc(data);
	while (i < data->map_height + val->map_first_i)
	{
		fill_row(data, val, i);
		i++;
	}
}

static void	fill_row(t_data *data, t_val *val, size_t i)
{
	size_t	j;
	size_t	str_len;

	str_len = ft_strlen(val->mapv[i]);
	j = 0;
	while (j < data->map_width)
	{
		if (j < str_len && val->mapv[i][j] == '1')
			data->map1[i - val->map_first_i][j] = 1;
		else if (j < str_len && (val->mapv[i][j] == '0'
			|| val->mapv[i][j] == 'N' || val->mapv[i][j] == 'S'
			|| val->mapv[i][j] == 'W' || val->mapv[i][j] == 'E'))
			data->map1[i - val->map_first_i][j] = 0;
		else if (j < str_len && (val->mapv[i][j] == 'D'))
			data->map1[i - val->map_first_i][j] = 3;
		else
			data->map1[i - val->map_first_i][j] = 2;
		j++;
	}
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
