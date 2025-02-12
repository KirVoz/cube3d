/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:44:16 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/12 05:06:18 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// free val->texture[all]->path, **map_v, 

void	map_validation(t_val *val)
{
	indetifiers_check(val);
	missing_indetifiers_check(val);
	texture_open_check(val);
	map_structure_check(val);
	starting_position_check(val);
	// for (int i = 0; val->map_v[i]; i++)
	// 	printf("%s\n", val->map_v[i]);
	// map_validity_check(val);
}

// void	map_validity_check(t_val *val)
// {
// 	if (is_map_closed(&val->map_v[8], 13))
// 		return ;
// 	int i = val->map_first_i;
// 	while (val->map_v[i])
// 	{
// 		printf("%s\n", val->map_v[i]);
// 		i++;
// 	}
// 	validation_error_msg("map is invalid", NULL);
// }
