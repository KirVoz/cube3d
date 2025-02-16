/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:18:56 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/15 19:33:14 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "cub3d.h"

typedef enum e_tex_type
{
	NO,
	SO,
	WE,
	EA,
	TEX_COUNT
}			t_tex_type;

typedef enum e_colour_type
{
	C,
	F,
	COLOURS_COUNT
}			t_col_type;

typedef struct s_texture_validation
{
	char	*path;
	int		counter;
	bool	was_parsed;

}			t_tex_val;

typedef struct s_colour_validation
{
	int		rgb[3];
	int		counter;
	bool	was_parsed;

}			t_col_val;

typedef struct s_validation
{
	int			fd;
	char		**mapv;
	t_tex_val	textures[TEX_COUNT];
	t_tex_type	tex_type;
	char		*tex_name[4];
	t_col_val	colours[COLOURS_COUNT];
	t_col_type	col_type;
	char		*col_name[2];
	size_t		indetifier_last_i;
	size_t		map_first_i;
	double		starting_pos[2];
	char		direction;
}				t_val;

// init
void		parser_main(t_val *val, char **argv);
void		data_init(t_val *val, t_data *data);
void		map_init(t_data *data, t_val *val);
// validator
void		extension_validation(char *map_path);
int			open_map_validation(char *map_path);
void		texture_open_validation(t_val *val);
void		map_validation(t_val *val);
size_t		check_inline_identifiers(char *line);
// identifiers/map_check
void		indetifiers_check(t_val *val);
void		missing_indetifiers_check(t_val *val);
void		map_structure_check(t_val *val);
void		starting_position_check(t_val *val);
// utils
void		texture_set(t_val *val, t_tex_type col_type, size_t ind);
void		colour_set(t_val *val, t_col_type col_type, size_t ind);

#endif