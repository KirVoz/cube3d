/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:58:08 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 17:58:12 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifdef __linux__
#  define LINUX 1
# else
#  define LINUX 0
# endif

# include "../libraries/Minilibx/mlx.h"
# include "../libraries/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "func.h"

# define WIDTH 1600
# define HEIGHT 800
# define TILE_SIZE 10
# define MINIMAP_SIZE_W 10
# define MINIMAP_SIZE_H 10
# define WALL_BUF 0.1
# define PI 3.14159265358979323846
# define FOV 60.0

#endif
