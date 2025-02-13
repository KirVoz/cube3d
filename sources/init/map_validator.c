/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:44:08 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/13 06:10:34 by aaleksee         ###   ########.fr       */
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

static size_t	map_start(char **mapv)
{
	size_t	i;

	i = 0;
	while (mapv[i])
	{
		if (is_valid_map_line(mapv[i]))
			return (i);
		i++;
	}
	return (0);
}

void	map_structure_check(t_val *val)
{
	size_t	i;

	val->map_first_i = map_start(val->mapv);
	if (val->map_first_i == 0)
		validation_error_msg("Map file should contain a map", NULL);
	if (val->map_first_i <= val->indetifier_last_i
		&& val->indetifier_last_i != 0)
		validation_error_msg("A map should be positioned after "
			"textures and colours identifiers", NULL);
	i = val->indetifier_last_i + 1;
	while (val->mapv[i])
	{
		if (!is_valid_map_line(val->mapv[i]))
		{
			full_print(val->mapv[i]); //del
			validation_error_msg("A map contains an incorrect symbol", NULL);
		}
		i++;
	}
}

static void	set_second_starting_position(t_val *val, size_t i)
{
	if (ft_strchr(val->mapv[i], 'N'))
	{
		val->starting_pos[1] = (ft_strchr(val->mapv[i], 'N') - val->mapv[i]);
		val->direction = 'N';
	}
	else if (ft_strchr(val->mapv[i], 'S'))
	{
		val->starting_pos[1] = (ft_strchr(val->mapv[i], 'S') - val->mapv[i]);
		val->direction = 'S';
	}
	else if (ft_strchr(val->mapv[i], 'W'))
	{
		val->starting_pos[1] = (ft_strchr(val->mapv[i], 'W') - val->mapv[i]);
		val->direction = 'W';
	}
	else if (ft_strchr(val->mapv[i], 'E'))
	{
		val->starting_pos[1] = (ft_strchr(val->mapv[i], 'E') - val->mapv[i]);
		val->direction = 'E';
	}
}

void	starting_position_check(t_val *val)
{
	size_t	i;
	size_t	counter;

	i = val->indetifier_last_i;
	counter = 0;
	while (val->mapv[i])
	{
		if (ft_strchr(val->mapv[i], 'N') || ft_strchr(val->mapv[i], 'S')
			|| ft_strchr(val->mapv[i], 'W') || ft_strchr(val->mapv[i], 'E'))
		{
			counter++;
			val->starting_pos[0] = i;
			set_second_starting_position(val, i);
		}
		if (counter > 1)
			validation_error_msg("You can set only one "
				"player on the map", NULL);
		i++;
	}
}
