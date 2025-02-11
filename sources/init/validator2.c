/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 03:44:37 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/11 02:26:08 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
