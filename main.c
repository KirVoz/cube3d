#include "cub3d.h"

void draw_map(t_data *data)
{
    int y, x, i, j, color;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            color = ((*data->map1)[y][x] == 1) ? 0xFFFFFF : 0x000000;

            for (i = 0; i < TILE_SIZE; i++)
            {
                for (j = 0; j < TILE_SIZE; j++)
                {
                    if (i == 0 || j == 0 || i == TILE_SIZE - 1 || j == TILE_SIZE - 1)
						my_mlx_pixel_put(data, x * TILE_SIZE + j, y * TILE_SIZE + i, 0xFF0000);
					else if ((*data->map1)[y][x] == 1)
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
void fill_background(t_data *data, int color)
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
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (keycode == 13 || keycode == 65362 || keycode == 119)
		data->w = 1;
	if (keycode == 0 || keycode == 65361 || keycode == 97)
		data->a = 1;
	if (keycode == 1 || keycode == 65364 || keycode == 115)
		data->s = 1;
	if (keycode == 2 || keycode == 65363 || keycode == 100)
		data->d = 1;
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 65362 || keycode == 119)
		data->w = 0;
	if (keycode == 0 || keycode == 65361 || keycode == 97)
		data->a = 0;
	if (keycode == 1  || keycode == 65364 || keycode == 115)
		data->s = 0;
	if (keycode == 2 || keycode == 65363 || keycode == 100)
		data->d = 0;
	return (0);
}


void move_player(t_data *data)
{
    double moveSpeed = 0.05; // Уменьшенная скорость перемещения
    double newPosX, newPosY;

    if (data->w)
    {
        newPosX = data->posX + data->dirX * moveSpeed;
        newPosY = data->posY + data->dirY * moveSpeed;
        if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0 && newPosY < MAP_HEIGHT && (*data->map1)[(int)newPosY][(int)newPosX] == 0)
        {
            data->posX = newPosX;
            data->posY = newPosY;
        }
    }
    if (data->s)
    {
        newPosX = data->posX - data->dirX * moveSpeed;
        newPosY = data->posY - data->dirY * moveSpeed;
        if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0 && newPosY < MAP_HEIGHT && (*data->map1)[(int)newPosY][(int)newPosX] == 0)
        {
            data->posX = newPosX;
            data->posY = newPosY;
        }
    }
    if (data->a)
    {
        newPosX = data->posX - data->planeX * moveSpeed;
        newPosY = data->posY - data->planeY * moveSpeed;
        if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0 && newPosY < MAP_HEIGHT && (*data->map1)[(int)newPosY][(int)newPosX] == 0)
        {
            data->posX = newPosX;
            data->posY = newPosY;
        }
    }
    if (data->d)
    {
        newPosX = data->posX + data->planeX * moveSpeed;
        newPosY = data->posY + data->planeY * moveSpeed;
        if (newPosX >= 0 && newPosX < MAP_WIDTH && newPosY >= 0 && newPosY < MAP_HEIGHT && (*data->map1)[(int)newPosY][(int)newPosX] == 0)
        {
            data->posX = newPosX;
            data->posY = newPosY;
        }
    }
}

void print_player(t_data *data, int color)
{
    int player = 5;
    int x, y;

    for (x = -player / 2; x < player / 2; x++)
    {
        for (y = -player / 2; y < player / 2; y++)
        {
            my_mlx_pixel_put(data, (int)(data->posX * TILE_SIZE) + x, (int)(data->posY * TILE_SIZE) + y, color);
        }
    }
}

int mouse_move(int x, int y, t_data *data)
{
    static int prevX = WIDTH / 2 + MAP_AREA_WIDTH / 2;
    static int prevY = HEIGHT / 2;

    double sense = 0.05;
    double rotSpeed = (x - prevX) * sense;
    double oldDirX = data->dirX;
    data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
    data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
    double oldPlaneX = data->planeX;
    data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
    data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);

    // double pitchSpeed = (y - prevY) * sense;
    data->pitch = y - prevY;
    // if (data->pitch > HEIGHT)
    //     data->pitch = HEIGHT / 4;
    // if (data->pitch < -HEIGHT)
    //     data->pitch = -HEIGHT / 4;
    mlx_mouse_move(data->win, WIDTH / 2 + MAP_AREA_WIDTH / 2, HEIGHT / 2);
    prevX = WIDTH / 2 + MAP_AREA_WIDTH / 2;
    prevY = HEIGHT / 2;
    return (0);
}

int render_next_frame(t_data *data)
{
	move_player(data);
    fill_background(data, 0x444444);
	draw_map(data);
    draw_scene(data);
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
    
    data.posX = 4.5;
    data.posY = 7.5;
    data.dirX = 0;
    data.dirY = -1;
    data.planeX = 0.66;
    data.planeY = 0;
    data.map1 = &map;
	data.w = 0;
	data.a = 0;
	data.s = 0;
	data.d = 0;
    data.pitch = 0;

	mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win, 3, 1L<<1, key_release, &data);
    // mlx_hook(data.win, 6, 1L<<6, mouse_move, &data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    mlx_loop(data.mlx);
    
    return (0);
}
