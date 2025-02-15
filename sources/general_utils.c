/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:22:17 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/15 16:25:44 by aaleksee         ###   ########.fr       */
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
