/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:44:16 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/15 15:26:14 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

bool	check_map_borders(char **map);
	// free val->texture[all]->path, **mapv, 

void	map_validation(t_val *val)
{
	indetifiers_check(val);
	missing_indetifiers_check(val);
	texture_open_check(val);
	map_structure_check(val);
	starting_position_check(val);
	for (int i = 0; val->mapv[i]; i++)
		printf("%s\n", val->mapv[i]);
	printf("Closed: %d\n", check_map_borders(&val->mapv[val->map_first_i]));
	if (!check_map_borders(&val->mapv[val->map_first_i]))
		validation_error_msg("A map doesn't have closed borders", NULL);
}

static size_t	count_rows(char **map)
{
	size_t	count;

	count = 0;
	while (map[count] != 0)
		count++;
	return (count);
}

static int	is_out_of_bounds(size_t i, size_t j, size_t total_rows, char **map)
{
	size_t	len;

	if (i >= total_rows)
		return (1);
	len = ft_strlen(map[i]);
	return (j >= len);
}

static size_t	is_border(char **map, size_t total_rows, size_t i, size_t j)
{
	if (is_out_of_bounds(i - 1, j, total_rows, map) || map[i - 1][j] == ' ')
		return (1);
	if (is_out_of_bounds(i + 1, j, total_rows, map) || map[i + 1][j] == ' ')
		return (1);
	if (is_out_of_bounds(i, j + 1, total_rows, map) || map[i][j + 1] == ' ')
		return (1);
	if (j == 0 || map[i][j - 1] == ' ')
		return (1);
	return (0);
}

bool	check_map_borders(char **map)
{
	size_t	rows;
	size_t	len;
	size_t	i;
	size_t	j;
	char	cell;

	rows = count_rows(map);
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		j = 0;
		while (j < len)
		{
			cell = map[i][j];
			if (cell != ' ')
				if (is_border(map, rows, i, j))
					if (cell != '1')
						return (false);
			j = j + 1;
		}
		i = i + 1;
	}
	return (true);
}
