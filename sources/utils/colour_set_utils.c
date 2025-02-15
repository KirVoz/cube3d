/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_set_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:47:44 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/15 15:11:41 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	validate_commas(t_val *val)
{
	size_t	i;
	char	*comma;

	i = 0;
	while (val->mapv[i])
	{
		comma = ft_strchr(val->mapv[i], ',');
		if (comma && *(comma + 1) == ',')
			validation_error_msg("Colours should be separated "
				"by only 1 comma", NULL);
		i++;
	}
}

static char	**colour_split(t_val *val, size_t ind)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 2;
	res = ft_split(&val->mapv[ind][j], ',');
	if (!res)
		exit_fail("Memory allocation in colour_set failed");
	while (res[i])
	{
		if (i > 3)
			validation_error_msg("RGB colours consist of 3 numbers", NULL);
		while (res[i][j] && res[i][j] != '\n')
		{
			if (!ft_isdigit(res[i][j]))
				validation_error_msg("Colour should consist "
					"only of digits", NULL);
			j++;
		}
		j = 0;
		i++;
	}
	return (res);
}

static void	set_rgb(t_val *val, t_col_type col_type, char **res, size_t ind)
{
	size_t	i;

	i = 0;
	while (res[i])
	{
		val->colours[col_type].rgb[i] = atoi(res[i]);
		i++;
	}
	i = 0;
	while (val->colours[col_type].rgb[i])
	{
		if (!(val->colours[col_type].rgb[i] >= 0 && val->colours[col_type].rgb[i] <= 255))
			validation_error_msg("RGB colour should be between 0 and 255", NULL);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	val->colours[col_type].counter++;
	if (val->colours[col_type].counter > 1)
		validation_error_msg("You can set only one RGB set of colours for the ",
			val->colours_name[col_type]);
	val->colours[col_type].was_parsed = true;
	if (ind + 1 > val->indetifier_last_i)
		val->indetifier_last_i = ind + 1;
}

void	colour_set(t_val *val, t_col_type col_type, size_t ind)
{
	char	**res;

	res = NULL;
	validate_commas(val);
	res = colour_split(val, ind);
	set_rgb(val, col_type, res, ind);
}
