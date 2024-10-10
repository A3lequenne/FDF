#include "fdf.h"

void	zoom_handler(float *x, float *y, int *z, t_fdf *map)
{
	// int	x_tmp;
	// int	y_tmp;

	*z = map->map_tab[(int)*y][(int)*x];
	*z *= map->zoom;
	*z *= map->hor_view;
	*y *= map->zoom;
	*x *= map->zoom;
	// y_tmp = *y;
	// x_tmp = *x;
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - *z;
}

void	put_pixel(t_fdf *map, int p_x, int p_y, int color)
{
	int		i;

	i = (p_x * map->data.pixel_bits / 8) + (p_y * map->data.line_bytes);
	map->data.img[i] = color;
	map->data.img[++i] = color >> 8;
	map->data.img[++i] = color >> 16;
}

int	get_fade_lvl(int hgt)
{
	if (hgt > 100)
		return (0xFFDF8D);
	if (hgt > 75)
		return (0xFFDE7A);
	if (hgt > 50)
		return (0xFFC568);
	if (hgt > 25)
		return (0xFD996B);
	if (hgt > 15)
		return (0xF7856C);
	if (hgt > 10)
		return (0xF06E6C);
	if (hgt > 5)
		return (0xD9576B);
	if (hgt > 0)
		return (0xA44369);
	if (hgt > -10)
		return (0x833F68);
	if (hgt > -20)
		return (0x833F68);
	if (hgt > -50)
		return (0x5E3C65);
	return (0x3F3A63);
}

void	draw_line(float x0, float y0, t_fdf *map)
{
	int		z0;
	int		z;
	float	x_step;
	float	y_step;
	int		max;

	zoom_handler(&x0, &y0, &z0, map);
	zoom_handler(&map->x, &map->y, &z, map);
	x0 += map->hor_move;
	y0 += map->ver_move;
	map->x += map->hor_move;
	map->y += map->ver_move;
	x_step = map->x - x0;
	y_step = map->y - y0;
	max = get_max(get_abs(x_step), get_abs(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x0 - map->x) || (int)(y0 - map->y))
	{
		if (x0 < 1000 && y0 < 800 && x0 > 0 && y0 > 0)
			put_pixel(map, x0, y0, get_fade_lvl(get_max(z0, z)));
		x0 += x_step;
		y0 += y_step;
	}
}

void	trace_line(t_fdf *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (j < map->width - 1)
			{
				map->x = j + 1;
				map->y = i;
				draw_line(j, i, map);
			}
			if (i < map->height - 1)
			{
				map->x = j;
				map->y = i + 1;
				draw_line(j, i, map);
			}
			j++;
		}
		i++;
	}
}