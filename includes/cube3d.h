#ifndef CUBE3D_H
# define CUBE3D_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include "../libraries/libft/libft.h"
// #include "../libraries/Minilibx/mlx.h"


// typedef struct	s_data
// {
// 	void	*mlx;
// 	void	*win;
// }			t_data;

// int		render_next_frame(t_data *data);
// #endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../libraries/libft/libft.h"
#include "../libraries/Minilibx/mlx.h"
#include "map.h"

#define WIDTH 800
#define HEIGHT 800
#define TILE_SIZE 10

typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;

    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;

    int **map1;
	int w, a, s, d;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void raycast(t_data *data);
void perform_dda(t_data *data, double rayDirX, double rayDirY, int *mapX, int *mapY, int *side);

#endif