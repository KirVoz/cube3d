#ifndef CUBE3D_H
# define CUBE3D_H
# ifndef __LINUX__
# define __LINUX__ 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../libraries/libft/libft.h"
#include "../libraries/Minilibx/mlx.h"
#include "map.h"
#include "func.h"
#include "init.h"

#define WIDTH 1600
#define HEIGHT 800
#define TILE_SIZE 10
#define MINIMAP_SIZE 10
#define PI 3.14159265358979323846
#define FOV 60.0
#define planeLen (FOV / 2 * PI / 180)

#endif
