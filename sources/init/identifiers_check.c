/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 03:44:37 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/16 15:57:53 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static char	*skip_whitespaces(char *mapv);

void	indetifiers_check(t_val *val)
{
	size_t	i;
	char	*line_without_wp;

	i = 0;
	while (val->mapv[i])
	{
		line_without_wp = skip_whitespaces(val->mapv[i]);
		if (!ft_strncmp(line_without_wp, "NO ", 3))
			texture_set(val, NO, i);
		else if (!ft_strncmp(line_without_wp, "SO ", 3))
			texture_set(val, SO, i);
		else if (!ft_strncmp(line_without_wp, "WE ", 3))
			texture_set(val, WE, i);
		else if (!ft_strncmp(line_without_wp, "EA ", 3))
			texture_set(val, EA, i);
		else if (!ft_strncmp(line_without_wp, "C ", 2))
			colour_set(val, C, i);
		else if (!ft_strncmp(line_without_wp, "F ", 2))
			colour_set(val, F, i);
		i++;
	}
	texture_open_validation(val);
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
				val->col_name[i]);
		i++;
	}
}

size_t	check_inline_identifiers(char *line)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == 'N')
			counter++;
		else if (line[i] == 'S')
			counter++;
		else if (line[i] == 'W')
			counter++;
		else if (line[i] == 'E')
			counter++;
		i++;
	}
	return (counter);
}

static char	*skip_whitespaces(char *mapv)
{
	size_t	i;

	i = 0;
	while (mapv[i] && mapv[i] == ' ')
		i++;
	return (&mapv[i]);
}
