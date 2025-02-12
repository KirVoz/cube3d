/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:44:08 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/12 05:16:30 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static bool	is_valid_map_line(char *line)
{
	size_t	j;

	j = 0;
	if (!line[j])
		return (false);
	while (line[j])
	{
		if (line[j] != '0' && line[j] != '1' && line[j] != ' '
			&& line[j] != 'N' && line[j] != 'S'
			&& line[j] != 'W' && line[j] != 'E')
			return (false);
		j++;
	}
	return (true);
}

static size_t	map_start(char **map_v)
{
	size_t	i;

	i = 0;
	while (map_v[i])
	{
		if (is_valid_map_line(map_v[i]))
			return (i);
		i++;
	}
	return (0);
}

void	map_structure_check(t_val *val)
{
	size_t	i;

	val->map_first_i = map_start(val->map_v);
	if (val->map_first_i == 0)
		validation_error_msg("Map file should contain a map", NULL);
	if (val->map_first_i <= val->indetifier_last_i
		&& val->indetifier_last_i != 0)
		validation_error_msg("A map should be positioned after "
			"textures and colours identifiers", NULL);
	i = val->indetifier_last_i + 1;
	while (val->map_v[i])
	{
		if (!is_valid_map_line(val->map_v[i]))
		{
			full_print(val->map_v[i]); //del
			validation_error_msg("A map contains an incorrect symbol", NULL);
		}
		i++;
	}
}

void	starting_position_check(t_val *val)
{
	size_t	i;
	size_t	counter;

	i = val->indetifier_last_i;
	counter = 0;
	while (val->map_v[i])
	{
		if (ft_strchr(val->map_v[i], 'N') || ft_strchr(val->map_v[i], 'S')
			|| ft_strchr(val->map_v[i], 'W') || ft_strchr(val->map_v[i], 'E'))
		{
			counter++;
			val->starting_pos[0] = i;
			val->starting_pos[1] = (ft_strchr(val->map_v[i], 'S')
					- val->map_v[i]); //to finish
		}
		if (counter > 1)
			validation_error_msg("You can set only one "
				"player on the map", NULL);
		i++;
	}
}
