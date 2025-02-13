/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:05 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/11 01:33:01 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	val_init(t_val *val)
{
	val->fd = 0;
	val->map = NULL;
	while (val->tex_type < TEX_COUNT)
	{
		val->textures[val->tex_type].counter = 0;
		val->textures[val->tex_type].was_parsed = false;
		val->tex_type++;
	}
	while (val->type < COLOURS_COUNT)
	{
		val->colours[val->tex_type].counter = 0;
		val->colours[val->tex_type].was_parsed = false;
		val->type++;
	}
	val->tex_type = 0;
	val->type = 0;
	init_names(val);
	val->indetifier_last_i = 0;
	val->map_first_i = 0;
}

void	init_names(t_val *val)
{
	val->tex_name[NO] = "north wall (NO)";
	val->tex_name[SO] = "south wall (SO)";
	val->tex_name[WE] = "west wall (WE)";
	val->tex_name[EA] = "east wall (EA)";
	val->colours_name[C] = "ceiling (C)";
	val->colours_name[F] = "floor (F)";
}

void	fix_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = '\0';
		i++;
	}
}
void	parser_main(char **argv, t_data *data)
{
	t_val	*val;

	val = (t_val *)s_alloc(1, sizeof(t_val));
	val_init(val);
	(void)data;
	extension_validation(argv[1]);
	val->fd = open_map_validation(argv[1]);
	val->map = read_map(val->fd);
	fix_map(val->map);
	//exit (0);
	close(val->fd);
	map_validation(val);
	// map_parser(map, data);
}

char	**read_map(int fd)
{
	char	**temp_map;
	size_t	size;
	size_t	i;

	size = 50;
	i = 0;
	temp_map = (char **)s_alloc(size, sizeof(char *));
	temp_map[i] = get_next_line(fd);
	while (temp_map[i] != NULL)
	{
		temp_map[++i] = get_next_line(fd);
		if (i == size - 1)
		{
			temp_map = s_realloc(temp_map, size * sizeof(char *),
					(size * 2) * sizeof(char *));
			size *= 2;
		}
	}
	temp_map[++i] = NULL;
	temp_map = s_realloc(temp_map, size, i);
	return (temp_map);
}


// char	*read_map(int fd)
// {
// 	char	*read;
// 	char	*temp_map;
// 	char	*temp_ptr;

// 	read = get_next_line(fd);
// 	if (!read)
// 		exit_fail("The file is empty");
// 	temp_map = ft_strjoin("", read);
// 	free(read);
// 	while (read)
// 	{
// 		read = get_next_line(fd);
// 		if (!read)
// 			break ;
// 		temp_ptr = temp_map;
// 		temp_map = ft_strjoin(temp_map, read);
// 		free(read);
// 		free(temp_ptr);
// 	}
// 	read = NULL;
// 	temp_ptr = NULL;
// 	return (temp_map);
// }
