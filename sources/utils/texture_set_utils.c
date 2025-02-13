/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_set_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:22:59 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/13 05:52:17 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static char	*find_path(char *str)
{
	size_t	i;
	char	*path;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "NO ", 3) || !ft_strncmp(&str[i], "SO ", 3)
			|| !ft_strncmp(&str[i], "WE ", 3) || !ft_strncmp(&str[i], "EA ", 3))
			i += 3;
		else if ((str[i] == 9 || str[i] == 32))
			i++;
		else
			break ;
	}
	path = ft_strdup(&(str[i]));
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = '\0';
	return(path);
}

void	texture_set(t_val *val, t_tex_type tex_type, size_t ind)
{
	val->textures[tex_type].path = find_path(val->mapv[ind]);
	val->textures[tex_type].counter++;
	if (val->textures[tex_type].counter > 1)
		validation_error_msg("You can set only one texture for the ",
			val->tex_name[tex_type]);
	val->textures[tex_type].was_parsed = true;
	if (ind + 1 > val->indetifier_last_i)
		val->indetifier_last_i = ind + 1;
}
