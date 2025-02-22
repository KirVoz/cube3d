/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:22:17 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/22 18:46:36 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	exit_fail(char *exit_message)
{
	write(2, exit_message, ft_strlen(exit_message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	validation_error_msg(char *msg, char *var)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	if (var)
		write(2, var, ft_strlen(var));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

t_data	*exit_free(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->map_height)
		free(data->map1[i++]);
	if (data->num_doors > 0)
		free((void *)data->door);
	free(data->map1);
	free(data);
	return (NULL);
}
