/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:47:44 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/17 10:15:02 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	validate_commas(t_val *val, size_t i);
static char	**colour_split(t_val *val, size_t ind, size_t split_start);
static void	parse_validate_rgb(t_val *val, t_col_type col_type, char **res);
static void	rgb_free(t_val *val, t_col_type col_type, char **res, size_t ind);

void	colour_set(t_val *val, t_col_type col_type, size_t ind)
{
	char	**res;
	size_t	split_start;

	res = NULL;
	split_start = 0;
	validate_commas(val, ind);
	while (val->mapv[ind][split_start] == ' ')
		split_start++;
	if (val->mapv[ind][split_start] == 'C'
		|| val->mapv[ind][split_start] == 'F')
		split_start++;
	while (val->mapv[ind][split_start] == ' ')
		split_start++;
	res = colour_split(val, ind, split_start);
	parse_validate_rgb(val, col_type, res);
	rgb_free(val, col_type, res, ind);
}

static void	validate_commas(t_val *val, size_t i)
{
	char	*comma;
	size_t	counter;

	comma = ft_strchr(val->mapv[i], ',');
	if (!comma)
		validation_error_msg("Each RGB should be separated by 1 comma", NULL);
	counter = 1;
	while (comma)
	{
		comma = ft_strchr(comma + 1, ',');
		if (comma)
			counter++;
		if (counter == 1 || counter > 2)
			validation_error_msg("Each RGB should be separated by 1 comma ",
				NULL);
	}
}

static char	**colour_split(t_val *val, size_t ind, size_t split_start)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	res = ft_split(&val->mapv[ind][split_start], ',');
	if (!res)
		exit_fail("Memory allocation in colour_set failed");
	while (res[i])
	{
		if (i > 3)
			validation_error_msg("RGB colour consist of 3 numbers", NULL);
		while (res[i][j] && res[i][j] != '\n')
		{
			if (!ft_isdigit(res[i][j]))
				validation_error_msg("RGB should be positive digits", NULL);
			j++;
		}
		j = 0;
		i++;
	}
	if (i < 3)
		validation_error_msg("RGB colour consists of 3 numbers", NULL);
	return (res);
}

static void	parse_validate_rgb(t_val *val, t_col_type col_type, char **res)
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
		if (!(val->colours[col_type].rgb[i] >= 0
				&& val->colours[col_type].rgb[i] <= 255))
			validation_error_msg("RGB colour should be between "
				"0 and 255", NULL);
		i++;
	}
}

static void	rgb_free(t_val *val, t_col_type col_type, char **res, size_t ind)
{
	size_t	i;

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
			val->col_name[col_type]);
	val->colours[col_type].was_parsed = true;
	if (ind > val->indetifier_last_i)
		val->indetifier_last_i = ind;
}
