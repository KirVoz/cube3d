#include "./includes/cube3d.h"

// void draw_map(t_data *data)
// {
// 	int y = 0, x, j, i, color;

// 	while (y < MAP_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < MAP_WIDTH)
// 		{
// 			if (data->map1[y][x] == 1)
// 				color =  0xFFFFFF;
// 			else if (data->map1[y][x] == 0)
// 				color = 0x000000;
// 			i = 0;
// 			while (i < TILE_SIZE)
// 			{
// 				j = 0;
// 				while (j < TILE_SIZE)
// 				{
// 					my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
// 					j++;
// 				}
// 				i++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

void draw_map(t_data *data)
{
    int y, x, i, j, color;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            color = (data->map1[y][x] == 1) ? 0xFFFFFF : 0x000000;

            for (i = 0; i < TILE_SIZE; i++)
            {
                for (j = 0; j < TILE_SIZE; j++)
                {
                    my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
                }
            }
        }
    }
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}
void fill_backgroung(t_data *data, int color)
{
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (keycode == 13)
		data->w = 1;
	if (keycode == 0)
		data->a = 1;
	if (keycode == 1)
		data->s = 1;
	if (keycode == 2)
		data->d = 1;
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == 13)
		data->w = 0;
	if (keycode == 0)
		data->a = 0;
	if (keycode == 1)
		data->s = 0;
	if (keycode == 2)
		data->d = 0;
	return (0);
}


void print_player(t_data *data, int color)
{
	int player = 5;
	int x = 0;
	int y = 0;

	while (x < player)
	{
		y = 0;
		while (y < player)
		{
			my_mlx_pixel_put(data, (int)(data->posX * TILE_SIZE) + x, (int)(data->posY * TILE_SIZE) + y, color);
			y++;
		}
		x++;
	}
}
void	move_player(t_data *data)
{
	if(data->w)
		data->posY -= 0.1;
	if(data->s)
		data->posY += 0.1;
	if(data->a)
		data->posX -= 0.1;
	if(data->d)
		data->posX += 0.1;
}

int render_next_frame(t_data *data)
{
	move_player(data);
    fill_backgroung(data, 0x444444);
	draw_map(data);
	//raycast(data);
	print_player(data, 0x00FF00);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);
    
    data.posX = 3;
    data.posY = 3;
    data.dirX = -1;
    data.dirY = 0;
    data.planeX = 0;
    data.planeY = 0.66;
    data.map1 = (int **)map;
	data.w = 0;
	data.a = 0;
	data.s = 0;
	data.d = 0;

	mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win, 3, 1L<<1, key_release, &data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    mlx_loop(data.mlx);
    
    return (0);
}
