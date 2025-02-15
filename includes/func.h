#ifndef FUNC_H
# define FUNC_H

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	double		moveSpeed;
}				t_keys;

typedef struct s_mouse
{
	double		sense;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;
}				t_mouse;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	double		pitch;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;

	int			**map1;
	size_t		map_height;
	size_t		map_width;

	char		**wall;
	t_keys		*keys;
	t_mouse		*mouse;
	t_texture	t[4];
}				t_data;

typedef struct s_ray
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		deltaDistX;
	double		deltaDistY;
	double		sideDistX;
	double		sideDistY;
	int			stepX;
	int			stepY;
	int			hit;
	char		hit_side;
	int			side;
	double		perpWallDist;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			x;
	int			y;
	int			color;
}				t_ray;

typedef struct s_viewer
{
	float		angle;
	float		angle_step;
	float		view_angle;
	float		start_angle;
	int			end_x;
	int			end_y;
	float		line_length;
	int			delta_x;
	int			delta_y;
	int			side_x;
	int			side_y;
	int			err;
	int			step_err;
	int			color;
	int			x0;
	int			y0;
}				t_viewer;

int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
void			move_player(t_data *data);
void			rotate_left_right(t_data *data, double rotSpeed);
int				check_collision(t_data *data, double newPosX, double newPosY);

void			draw_map(t_data *data);
void			draw_scene(t_data *data);
void			fill_floor(t_data *data, int color);
void			fill_sealing(t_data *data, int color);
void			fill_map(t_data *data, int color);
void			print_player(t_data *data, int color);
int				mouse_move(int x, int y, t_data *data);

int				render_next_frame(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

int				close_cub(t_data *data);
void			hooks(t_data *data);

void			draw_viewing_angle(t_data *data, int color);
void			draw_lines(t_data *data, t_viewer *v);

void			init_main(char **argv, t_data *game);

// utils
void			exit_fail(char *exit_message);
void			validation_error_msg(char *msg, char *var);
void	full_print(char *str); // del
// end of utils

// memory managment
void			*s_alloc(size_t count, size_t size);
void			*s_realloc(void *ptr, size_t old_size, size_t new_size);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
