/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_set_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:22:59 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/12 05:16:24 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static char	*find_path(char *str)
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

void	texture_set(t_val *val, t_tex_type col_type, size_t ind)
{
	val->textures[col_type].path = find_path(val->map_v[ind]);
	val->textures[col_type].counter++;
	if (val->textures[col_type].counter > 1)
		validation_error_msg("You can set only one texture for the ",
			val->tex_name[col_type]);
	val->textures[col_type].was_parsed = true;
	if (ind + 1 > val->indetifier_last_i)
		val->indetifier_last_i = ind + 1;
}
