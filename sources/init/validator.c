/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:44:16 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/11 02:56:51 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// free val->texture[all]->path, **map, 

void	map_validation(t_val *val)
{
	indetifiers_check(val);
	missing_indetifiers_check(val);
	texture_open_check(val);
	map_structure_check(val);
	starting_position_check(val);
	map_validity_check(val);
}

void	map_validity_check(t_val *val)
{
	if (flood_fill(val->map, val->starting_pos[0], val->starting_pos[1]))
		return ;

	int i = val->map_first_i;
	while (val->map[i])
	{
		printf("%s\n", val->map[i]);
		i++;
	}
	validation_error_msg("map is invalid", NULL);
}

static int	flood_fill_helper(char **map, int x, int y)
{
	if (map[x][y] == '2')
		return (0);
	else if (map[x][y] != '1')
	{
		if (map[x][y] == '0')
			map[x][y] = '2';
		return (flood_fill(map, x, y));
	}
	return (0);
}

int	flood_fill(char **map, int x, int y)
{
	if (flood_fill_helper(map, x, y + 1))
		return (1);
	if (flood_fill_helper(map, x, y - 1))
		return (1);
	if (flood_fill_helper(map, x + 1, y))
		return (1);
	if (flood_fill_helper(map, x - 1, y))
		return (1);
	return (0);
}

void	starting_position_check(t_val *val)
{
	size_t	i;
	size_t	counter;

	i = val->indetifier_last_i;
	counter = 0;
	while(val->map[i])
	{
		if (ft_strchr(val->map[i], 'N') || ft_strchr(val->map[i], 'S')
			|| ft_strchr(val->map[i], 'W') || ft_strchr(val->map[i], 'E'))
			{
			counter++;
			val->starting_pos[0] = i;
			val->starting_pos[1] = ft_strchr(val->map[i], 'S') - val->map[i];;
			printf("%zu - %zu\n", val->starting_pos[0], val->starting_pos[1]);
			}
		if (counter > 1)
			validation_error_msg("You can set only one "
			"player on the map", NULL);
		i++;
	}
}

void	map_structure_check(t_val *val)
{
	size_t i;

	val->map_first_i = map_start(val->map);
	if (val->map_first_i == 0)
		validation_error_msg("Map file should contain a map", NULL);
	if (val->map_first_i <= val->indetifier_last_i
		&& val->indetifier_last_i != 0)
		validation_error_msg("A map should be positioned after "
			"textures and colours identifiers", NULL);
	i = val->indetifier_last_i + 1;
	while (val->map[i])
	{
		if (!is_valid_map_line(val->map[i]))
			validation_error_msg("A map contains an incorrect symbol", NULL);
		i++;
	}
}

size_t	map_start(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (is_valid_map_line(map[i]))
			return (i);
		i++;
	}
	return (0);
}

bool	is_valid_map_line(char *line)
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

void	missing_indetifiers_check(t_val *val)
{
	size_t	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (val->textures[i].was_parsed == false)
			validation_error_msg("You need to set texture for the ",
		val->tex_name[i]);
		i++;
	}
	i = 0;
	while (i < COLOURS_COUNT)
	{
		if (val->colours[i].was_parsed == false)
			validation_error_msg("You need to set colours for the ",
		val->colours_name[i]);
		i++;
	} 
}

void	indetifiers_check(t_val *val)
{
	size_t	i;

	i = 0;
	while (val->map[i])
	{
		if (!ft_strncmp(val->map[i], "NO ", 3))
			texture_set(val, NO, i);
		else if (!ft_strncmp(val->map[i], "SO ", 3))
			texture_set(val, SO, i);
		else if (!ft_strncmp(val->map[i], "WE ", 3))
			texture_set(val, WE, i);
		else if (!ft_strncmp(val->map[i], "EA ", 3))
			texture_set(val, EA, i);
		else if (!ft_strncmp(val->map[i], "C ", 2))
			colour_set(val, C, i);
		else if (!ft_strncmp(val->map[i], "F ", 2))
			colour_set(val, F, i);
		i++;
	}

}

void	texture_set(t_val *val, t_tex_type type, size_t ind)
{
	val->textures[type].path = find_path(val->map[ind]);
	val->textures[type].counter++;
	if (val->textures[type].counter > 1)
		validation_error_msg("You can set only one texture for the ",
		val->tex_name[type]);
	val->textures[type].was_parsed = true;
	if (ind + 1 > val->indetifier_last_i)
		val->indetifier_last_i = ind + 1;
}

void	colour_set(t_val *val, t_col_type type, size_t ind)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 2;
	while (val->map[i])
	{
		char	*comma;
		comma = ft_strchr(val->map[i], ',');
		if (comma && *(comma + 1) == ',')
			validation_error_msg("Colours should be separated by only 1 comma", NULL);
		i++;
	}

	i = 0;
	res = ft_split(&val->map[ind][j], ',');
	if (!res)
		exit_fail("Memory allocation in colour_set failed");

	while (res[i])
	{
		if (i > 3)
			validation_error_msg("RGB colours consist of 3 numbers", NULL);
		while (res[i][j] && res[i][j] != '\n')
		{
			if (!ft_isdigit(res[i][j]))
				validation_error_msg("Colour should consist only of digits", NULL);
			j++;
		}
		j = 0;
		i++;
	}

	i = 0;
	while(res[i])
	{
		val->colours[type].rgb[i] = atoi(res[i]);
		i++;
	}
	while(res[--i])
		free(res[i]);
	free(res);

	i = 0;
	while (val->colours[type].rgb[i])
	{
		if (!(val->colours[type].rgb[i] >= 0 && val->colours[type].rgb[i] <= 255))
			validation_error_msg("RGB colour should be between 0 and 255", NULL);
		i++;
	}
	val->colours[type].counter++;
	if (val->colours[type].counter > 1)
		validation_error_msg("You can set only one RGB set of colours for the ",
		val->colours_name[type]);
	val->colours[type].was_parsed = true;
	if (ind + 1 > val->indetifier_last_i)
		val->indetifier_last_i = ind + 1;
}

char	*find_path(char *str)
{
	size_t	i;
	char	*path;

	i = 2;
	while (str[i] && (str[i] == 9 || str[i] == 32))
		i++;
	path = ft_strdup(&(str[i]));
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = '\0';
	return(path);
}

void	texture_open_check(t_val *val)
{
	size_t	i;
	int		fd;

	i = 0;
	while (i < TEX_COUNT)
	{
		fd = open(val->textures[i].path, O_RDONLY);
		if (fd == -1)
			validation_error_msg("Unable to open texture file for the ", val->tex_name[i]);
		close(fd);
		i++;
	}
}
