/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:44:16 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/12 18:33:51 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// free val->texture[all]->path, **mapv, 

void	map_validation(t_val *val)
{
	indetifiers_check(val);
	missing_indetifiers_check(val);
	texture_open_check(val);
	map_structure_check(val);
	starting_position_check(val);
	// for (int i = 0; val->mapv[i]; i++)
	// 	printf("%s\n", val->mapv[i]);
	// map_validity_check(val);
}

// void	map_validity_check(t_val *val)
// {
// 	if (is_map_closed(&val->mapv[8], 13))
// 		return ;
// 	int i = val->map_first_i;
// 	while (val->mapv[i])
// 	{
// 		printf("%s\n", val->mapv[i]);
// 		i++;
// 	}
// 	validation_error_msg("map is invalid", NULL);
// }
