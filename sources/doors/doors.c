#include "cub3d.h"
void door_init(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (++i < (int)data->map_height)
	{
		j = -1;
		while (++j < (int)data->map_width)
		{
			if (data->map1[i][j] == 3)
			{
				data->door[k].x = j;
				data->door[k].y = i;
				data->door[k].state = DOOR_CLOSED;
				data->door[k].anim_progress = DOOR_CLOSED;
				k++;
			}
		}
	}
	data->num_doors = k;
	data->doors_anim_speed = 0.02f;
}

t_door *get_door(t_data *data, int x, int y)
{
    int i;

    i = 0;
    while (i < data->num_doors)
    {
        if (data->door[i].x == x && data->door[i].y == y)
            return &data->door[i];
        i++;
    }
    return NULL;
}

void interact_with_doors(t_data *data)
{
	int	i;
	int	p_x;
	int	p_y;

	p_x = (int)(data->posX + data->dirX);
	p_y = (int)(data->posY + data->dirY);
	i = -1;
	while (++i < data->num_doors)
	{
		printf("door[%d].x = %d, door[%d].y = %d\n", i, data->door[i].x, i, data->door[i].y);
		if (data->door[i].x == p_x && data->door[i].y == p_y)
		{
			if (data->door[i].state == DOOR_OPEN)
				data->door[i].state = DOOR_CLOSING;
			else
				data->door[i].state = DOOR_OPENING;
		}
	}
}

void door_animation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_doors)
	{
		if (data->door[i].state == DOOR_OPENING)
		{
			data->door[i].anim_progress += data->doors_anim_speed;
			if (data->door[i].anim_progress >= 1.0f)
			{
				data->door[i].anim_progress = 1.0f;
				data->door[i].state = DOOR_OPEN;
			}
		}
		else if (data->door[i].state == DOOR_CLOSING)
		{
			data->door[i].anim_progress -= data->doors_anim_speed;
			if (data->door[i].anim_progress <= 0.0f)
			{
				data->door[i].anim_progress = 0.0f;
				data->door[i].state = DOOR_CLOSED;
			}
		}
	}
}

void draw_doors(t_data *data)
{
    int i;
    int j;
    int x;
    int y;
    int color;

    i = -1;
    while (++i < data->num_doors)
    {
        x = data->door[i].x * TILE_SIZE;
        y = data->door[i].y * TILE_SIZE;
        j = -1;
        while (++j < TILE_SIZE)
        {
            if (data->door[i].state == DOOR_OPENING)
                color = 0x00FF00; // Зеленый цвет для открывающейся двери
            else if (data->door[i].state == DOOR_CLOSING)
                color = 0xFFF000; // Красный цвет для закрывающейся двери
            else if (data->door[i].state == DOOR_OPEN)
                color = 0x00FF00; // Зеленый цвет для открытой двери
            else
                color = 0xF00000; // Красный цвет для закрытой двери

            // Отрисовка двери с учетом прогресса анимации
            int door_height = (int)(TILE_SIZE * data->door[i].anim_progress);
            int y_offset = TILE_SIZE - door_height;
            int k = -1;
            while (++k < door_height)
                my_mlx_pixel_put(data, x, y + y_offset + k, color);
        }
    }
}
