#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}



int mouse_move(int x, int y, t_data *data)
{
    static int prevX = WIDTH / 2;
    static int prevY = HEIGHT / 2;

    double sense = 0.05;
    double rotSpeed = (x - prevX) * sense;
    double oldDirX = data->dirX;
    data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
    data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
    double oldPlaneX = data->planeX;
    data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
    data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
    data->pitch = y - prevY;
    mlx_mouse_move(data->win, WIDTH / 2, HEIGHT / 2);
    prevX = WIDTH / 2;
    prevY = HEIGHT / 2;
    return (0);
}

int close_cub(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

void hooks(t_data *data)
{
    mlx_hook(data->win, 2, 1L<<0, key_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_release, data);
    mlx_hook(data->win, 17, 1L<<17, close_cub, data);
    // mlx_hook(data->win, 6, 1L<<6, mouse_move, data); // macos
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
    data.left = 0;
    data.right = 0;
    data.pitch = 0;
    data.rotSpeed = 1 * (M_PI / 180);

    hooks(&data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    mlx_loop(data.mlx);
    
    return (0);
}
