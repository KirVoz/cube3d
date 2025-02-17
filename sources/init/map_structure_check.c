/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_structure_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:44:08 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/17 10:26:21 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static size_t	map_start(char **mapv);
static bool		is_valid_map_line(char *line);
static double	set_x_starting_position(t_val *val, size_t i);

void	map_structure_check(t_val *val)
{
	size_t	i;
	char	*map_requirments;

	map_requirments = "\nThe valid map should have closed borders of 1's"
		"\nIt contains only following symbols: 1, 0, N, S, W, E, D";
	val->map_first_i = map_start(val->mapv);
	if (val->map_first_i == 0)
		validation_error_msg("Map file should contain a map", map_requirments);
	if (val->map_first_i <= val->indetifier_last_i
		&& val->indetifier_last_i != 0)
		validation_error_msg("A map should be positioned after "
			"textures and colours identifiers", map_requirments);
	i = val->map_first_i;
	while (val->mapv[i])
	{
		if (!is_valid_map_line(val->mapv[i]))
			validation_error_msg("A map contains an incorrect symbol",
				map_requirments);
		i++;
	}
}

void	starting_position_check(t_val *val)
{
	size_t	i;
	size_t	counter;

	i = val->map_first_i;
	counter = 0;
	while (val->mapv[i])
	{
		if (ft_strchr(val->mapv[i], 'N') || ft_strchr(val->mapv[i], 'S')
			|| ft_strchr(val->mapv[i], 'W') || ft_strchr(val->mapv[i], 'E'))
		{
			counter = check_inline_identifiers(val->mapv[i]);
			val->starting_pos[0] = set_x_starting_position(val, i);
			val->starting_pos[1] = i;
		}
		if (counter > 1)
			validation_error_msg("You can set only one "
				"player on the map", NULL);
		i++;
	}
	if (counter == 0)
		validation_error_msg("You need to set at least one player", NULL);
	val->starting_pos[0] += 0.5;
	val->starting_pos[1] -= val->map_first_i - 0.5;
}

static size_t	map_start(char **mapv)
{
	size_t	i;

	i = 0;
	while (mapv[i])
	{
		if (is_valid_map_line(mapv[i]))
			break ;
		i++;
	}
	while (i)
	{
		i--;
		if (mapv[i][0] == '\0' || mapv[i][0] == '\n')
			return (i + 1);
	}
	return (0);
}

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
			&& line[j] != 'W' && line[j] != 'E'
			&& line[j] != 'D')
			return (false);
		j++;
	}
	return (true);
}

static double	set_x_starting_position(t_val *val, size_t i)
{
	double	starting_pos_x;

	starting_pos_x = 0;
	if (ft_strchr(val->mapv[i], 'N'))
	{
		starting_pos_x = (ft_strchr(val->mapv[i], 'N') - val->mapv[i]);
		val->direction = 'N';
	}
	else if (ft_strchr(val->mapv[i], 'S'))
	{
		starting_pos_x = (ft_strchr(val->mapv[i], 'S') - val->mapv[i]);
		val->direction = 'S';
	}
	else if (ft_strchr(val->mapv[i], 'W'))
	{
		starting_pos_x = (ft_strchr(val->mapv[i], 'W') - val->mapv[i]);
		val->direction = 'W';
	}
	else if (ft_strchr(val->mapv[i], 'E'))
	{
		starting_pos_x = (ft_strchr(val->mapv[i], 'E') - val->mapv[i]);
		val->direction = 'E';
	}
	return (starting_pos_x);
}
