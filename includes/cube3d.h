#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libft.h"
#include "../libraries/minilibx-linux/mlx.h"


typedef struct	s_data
{
	void	*mlx;
	void	*win;
}			t_data;

int		render_next_frame(t_data *data);
#endif
