/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:59:32 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 17:59:35 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_door_progress(t_door *door)
{
	if (door->state == DOOR_OPENING)
	{
		door->anim_progress += 0.01f;
		if (door->anim_progress >= 1.0f)
		{
			door->anim_progress = 1.0f;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->anim_progress -= 0.01f;
		if (door->anim_progress <= 0.0f)
		{
			door->anim_progress = 0.0f;
			door->state = DOOR_CLOSED;
		}
	}
}

static void	update_door_texture(t_data *data, t_door *door)
{
	int	frame;

	frame = (int)(door->anim_progress * 4);
	if (frame > 3)
		frame = 3;
	door->t = data->tex.t[frame];
}

void	door_animation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_doors)
	{
		update_door_progress(&data->door[i]);
		update_door_texture(data, &data->door[i]);
	}
}
