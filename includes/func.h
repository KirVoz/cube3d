#ifndef FUNC_H
# define FUNC_H

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;

	double	pitch;
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;

	int (*map1)[MAP_HEIGHT][MAP_WIDTH];
	int w, a, s, d;
	int left, right;
	double sense, rotSpeed, oldDirX, oldPlaneX;
}			t_data;

typedef struct s_ray
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	int		hit;
	char	hit_side;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		x;
	int		y;
	int		color;
}			t_ray;

int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
void		move_player(t_data *data);

void		draw_map(t_data *data);
void		draw_scene(t_data *data);
void		fill_floor(t_data *data, int color);
void		fill_sealing(t_data *data, int color);
void		print_player(t_data *data, int color);
int			mouse_move(int x, int y, t_data *data);

int			render_next_frame(t_data *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

int			close_cub(t_data *data);
void		hooks(t_data *data);

#endif
