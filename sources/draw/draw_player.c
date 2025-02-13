#include "../includes/cub3d.h"

void	draw_player_pixel(t_data *data, int x, int y, int color)
{
	my_mlx_pixel_put(data, (int)(data->posX * TILE_SIZE) + x, (int)(data->posY
			* TILE_SIZE) + y, color);
}

void	print_player(t_data *data, int color)
{
	int	player;
	int	x;
	int	y;

	player = 5;
	x = -player / 2;
	while (x < player / 2)
	{
		y = -player / 2;
		while (y < player / 2)
		{
			draw_player_pixel(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_viewing_angle(t_data *data, int color)
{
	t_viewer	v;

	v.color = color;
	v.line_length = 200.0;
	v.angle_step = M_PI / 180;
	v.view_angle = M_PI / 3;
	v.start_angle = atan2(data->dirY, data->dirX) - v.view_angle / 2;
	v.angle = v.start_angle;
	while (v.angle <= v.start_angle + v.view_angle)
	{
		v.end_x = (int)(data->posX * TILE_SIZE + v.line_length * cos(v.angle));
		v.end_y = (int)(data->posY * TILE_SIZE + v.line_length * sin(v.angle));
		draw_lines(data, &v);
		v.angle += v.angle_step;
	}
}

static void	validate_v(t_data *data, t_viewer *v)
{
	v->x0 = (int)(data->posX * TILE_SIZE);
	v->y0 = (int)(data->posY * TILE_SIZE);
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
			if ((*data->map1)[v->y0 / TILE_SIZE][v->x0 / TILE_SIZE] == 1)
				break ;
			my_mlx_pixel_put(data, v->x0, v->y0, v->color);
		}
		if (v->x0 == v->end_x && v->y0 == v->end_y)
			break ;
		v->err_tmp = v->err;
		if (v->err_tmp > -v->delta_x)
		{
			v->err -= v->delta_y;
			v->x0 += v->side_x;
		}
		if (v->err_tmp < v->delta_y)
		{
			v->err += v->delta_x;
			v->y0 += v->side_y;
		}
	}
}
