/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:40:59 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/17 08:53:22 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	extension_validation(char *map_path)
{
	char	*str;

	str = ft_strrchr(map_path, '.');
	if (!str)
		exit_fail("Map should have .cub extenstion");
	if (ft_strncmp(str, ".cub", ft_strlen(str) + 1))
		exit_fail("Map should have .cub extenstion");
}

int	open_map_validation(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit_fail("Unable to open a map file");
	return (fd);
}

void	texture_open_validation(t_val *val)
{
	size_t	i;
	int		fd;

	i = 0;
	while (i < TEX_COUNT)
	{
		fd = open(val->textures[i].path, O_RDONLY);
		if (fd == -1)
			validation_error_msg("Unable to open "
				"texture file for the ", val->tex_name[i]);
		close(fd);
		i++;
	}
}
