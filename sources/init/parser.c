/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:05 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/16 19:40:58 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	val_init(t_val *val);
static void	init_names(t_val *val);
static char	**read_map(int fd);

void	parser_main(t_val *val, char **argv)
{
	val_init(val);
	extension_validation(argv[1]);
	val->fd = open_map_validation(argv[1]);
	val->mapv = read_map(val->fd);
	close(val->fd);
	map_validation(val);
}

static void	val_init(t_val *val)
{
	val->fd = 0;
	val->mapv = NULL;
	while (val->tex_type < TEX_COUNT)
	{
		val->textures[val->tex_type].counter = 0;
		val->textures[val->tex_type].was_parsed = false;
		val->tex_type++;
	}
	while (val->col_type < COLOURS_COUNT)
	{
		val->colours[val->tex_type].counter = 0;
		val->colours[val->tex_type].was_parsed = false;
		val->col_type++;
	}
	val->tex_type = 0;
	val->col_type = 0;
	init_names(val);
	val->indetifier_last_i = 0;
	val->map_first_i = 0;
}

static void	init_names(t_val *val)
{
	val->tex_name[NO] = "north wall (NO)";
	val->tex_name[SO] = "south wall (SO)";
	val->tex_name[WE] = "west wall (WE)";
	val->tex_name[EA] = "east wall (EA)";
	val->col_name[C] = "ceiling (C)";
	val->col_name[F] = "floor (F)";
}

static char	**read_map(int fd)
{
	char	**val_map;
	size_t	size;
	size_t	i;

	size = 50;
	i = 0;
	val_map = (char **)s_alloc(size, sizeof(char *));
	val_map[i] = get_next_line(fd);
	if (val_map[i] && val_map[i][ft_strlen(val_map[i]) - 1] == '\n')
		val_map[i][ft_strlen(val_map[i]) - 1] = '\0';
	while (val_map[i] != NULL)
	{
		val_map[++i] = get_next_line(fd);
		if (val_map[i] && val_map[i][ft_strlen(val_map[i]) - 1] == '\n')
			val_map[i][ft_strlen(val_map[i]) - 1] = '\0';
		if (i == size - 1)
		{
			val_map = (char **)s_realloc(val_map, size * sizeof(char *),
					(size * 2) * sizeof(char *));
			size *= 2;
		}
	}
	val_map[++i] = NULL;
	val_map = s_realloc(val_map, size * sizeof(char *), i * sizeof(char *));
	return (val_map);
}
