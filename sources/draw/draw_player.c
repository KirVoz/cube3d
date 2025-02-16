#include "cub3d.h"

void	print_player(t_data *data, int color)
{
	int	player;
	int	x;
	int	y;

	player = 5.0;
	x = -player / 2;
	while (x < player / 2)
	{
		y = -player / 2;
		while (y < player / 2)
		{
			my_mlx_pixel_put(data, (MINIMAP_SIZE_W / 2) * TILE_SIZE + x
				+ TILE_SIZE / 2, (MINIMAP_SIZE_H / 2) * TILE_SIZE + y
				+ TILE_SIZE / 2, color);
			y++;
		}
		x++;
	}
}

void	draw_viewing_angle(t_data *data, int color)
{
	t_viewer	v;

	v.color = color;
	v.line_length = 50;
	v.angle_step = PI / 180;
	v.view_angle = PI / 3;
	v.start_angle = atan2(data->dirY, data->dirX) - v.view_angle / 2;
	v.angle = v.start_angle;
	while (v.angle <= v.start_angle + v.view_angle)
	{
		v.end_x = (int)((MINIMAP_SIZE_W / 2) * TILE_SIZE + v.line_length
				* cos(v.angle) + TILE_SIZE / 2);
		v.end_y = (int)((MINIMAP_SIZE_H / 2) * TILE_SIZE + v.line_length
				* sin(v.angle) + TILE_SIZE / 2);
		draw_lines(data, &v);
		v.angle += v.angle_step;
	}
}

static void	validate_v(t_data *data, t_viewer *v)
{
	(void)data;
	v->x0 = (int)(((MINIMAP_SIZE_W) / 2) * TILE_SIZE + TILE_SIZE / 2);
	v->y0 = (int)(((MINIMAP_SIZE_H) / 2) * TILE_SIZE + TILE_SIZE / 2);
	v->delta_x = abs(v->end_x - v->x0);
	v->delta_y = abs(v->end_y - v->y0);
	if (v->x0 < v->end_x)
		v->side_x = 1;
	else
		v->side_x = -1;
	if (v->y0 < v->end_y)
		v->side_y = 1;
	else
		v->side_y = -1;
	if (v->delta_x > v->delta_y)
		v->err = v->delta_x / 2;
	else
		v->err = -v->delta_y / 2;
}

void	draw_lines(t_data *data, t_viewer *v)
{
	validate_v(data, v);
	while (1)
	{
		if (v->x0 >= 0 && v->x0 < WIDTH && v->y0 >= 0 && v->y0 < HEIGHT)
		{
			if (data->map1[(int)(data->posY - MINIMAP_SIZE_H / 2 + v->y0
					/ TILE_SIZE)][(int)(data->posX - MINIMAP_SIZE_W / 2 + v->x0
					/ TILE_SIZE)] == 1)
				break ;
			my_mlx_pixel_put(data, v->x0, v->y0, v->color);
		}
		if (v->x0 == v->end_x && v->y0 == v->end_y)
			break ;
		v->step_err = v->err;
		if (v->step_err > -v->delta_x)
		{
			v->err -= v->delta_y;
			v->x0 += v->side_x;
		}
		if (v->step_err < v->delta_y)
		{
			v->err += v->delta_x;
			v->y0 += v->side_y;
		}
	}
}
