/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:58:27 by kvoznese          #+#    #+#             */
/*   Updated: 2025/02/22 18:47:49 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}					t_door_state;

typedef enum e_tex_type
{
	NO,
	SO,
	WE,
	EA,
	TEX_COUNT
}					t_tex_type;

typedef enum e_colour_type
{
	C,
	F,
	COLOURS_COUNT
}					t_col_type;

typedef struct s_draw_texture
{
	double			hit;
	int				d;
	int				tex_x;
	int				tex_y;
	int				color;
}					t_draw_texture;

typedef struct s_draw_map
{
	int				x;
	int				y;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				color;
}					t_draw_map;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct s_door
{
	t_door_state	state;
	int				x;
	int				y;
	float			anim_progress;
	t_texture		t;
}					t_door;

typedef struct s_doors_tex
{
	t_texture		t[4];
}					t_doors_tex;

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				door;
	int				door_pressed;
	int				left;
	int				right;
	double			ms;
}					t_keys;

typedef struct s_mouse
{
	double			sense;
	double			rot_speed;
	double			old_d_x;
	double			old_pl_x;
}					t_mouse;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	double			pitch;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

	int				**map1;
	size_t			map_height;
	size_t			map_width;

	char			**wall;
	t_keys			keys;
	t_mouse			mouse;
	t_texture		t[TEX_COUNT];
	int				colours[COLOURS_COUNT];

	t_door			*door;
	t_doors_tex		tex;
	int				num_doors;
	int				game_over;
}					t_data;

typedef struct s_ray
{
	double			cam_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	char			hit_side;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				x;
	int				y;
	int				color;
}					t_ray;

typedef struct s_viewer
{
	float			angle;
	float			angle_step;
	float			view_angle;
	float			start_angle;
	int				end_x;
	int				end_y;
	float			line_length;
	int				delta_x;
	int				delta_y;
	int				side_x;
	int				side_y;
	int				err;
	int				step_err;
	int				color;
	int				x0;
	int				y0;
}					t_viewer;

int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
void				move_player(t_data *data);
void				rotate_left_right(t_data *data, double rot_speed);
int					check_collision(t_data *data, double newpos_x,
						double newpos_y);

void				draw_map(t_data *data);
void				draw_scene(t_data *data);
void				draw_tile(t_data *data, int x, int y, int color);
void				draw_tile_border(t_data *data, int x, int y);
void				fill_floor(t_data *data, int color);
void				fill_ceiling(t_data *data, int color);
void				fill_map(t_data *data, int color);
void				print_player(t_data *data, int color);
int					mouse_move(int x, int y, t_data *data);

void				what_texture(t_texture **t, t_ray ray, t_data *data);
void				init_ray(t_data *data, t_ray *ray);
void				init_ray2(t_data *data, t_ray *ray);
void				what_side(t_ray *ray);

int					render_next_frame(t_data *data);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);

int					close_cub(t_data *data);
void				hooks(t_data *data);

void				draw_viewing_angle(t_data *data, int color);
void				draw_lines(t_data *data, t_viewer *v);

void				exit_fail(char *exit_message);
void				validation_error_msg(char *msg, char *var);
void				*s_alloc(size_t count, size_t size);
void				*s_realloc(void *ptr, size_t old_size, size_t new_size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void				door_init(t_data *data);
void				count_doors(t_data *data);
void				draw_door(t_data *data, t_ray ray);
void				check_door_interaction(t_data *data);
void				toggle_door(t_data *data, int x, int y);
void				door_animation(t_data *data);
void				draw_texture(t_data *data, t_ray *ray, t_texture *t);
int					check_door(t_data *data, int pos_x, int pos_y);
t_data				*exit_free(t_data *data);

#endif
