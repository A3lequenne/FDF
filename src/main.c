#include "fdf.h"

void	draw_backg(t_fdf *map, int color)
{
	int	x;
	int	y;

	y = 0;
	while (++y < 800)
	{
		x = 0;
		while (++x < 1000)
			put_pixel(map, x, y, color);
	}
}

void	show_commands(t_fdf *map)
{
	mlx_string_put (map->p_mlx, map->p_win, 20, 10, 0xFFFFFF, "<< COMMANDS >>");
	mlx_string_put (map->p_mlx, map->p_win, 20, 30, 0xFFFFFF, "W - Move up");
	mlx_string_put (map->p_mlx, map->p_win, 20, 50, 0xFFFFFF, "S - Move down");
	mlx_string_put (map->p_mlx, map->p_win, 20, 70, 0xFFFFFF, "A - Move left");
	mlx_string_put (map->p_mlx, map->p_win, 20, 90,
		0xFFFFFF, "D - Move right");
	mlx_string_put(map->p_mlx, map->p_win, 20, 110,
		0xFFFFFF, "R - Increase depth");
	mlx_string_put (map->p_mlx, map->p_win, 20, 130,
		0xFFFFFF, "F - Decrease depth");
}

void	draw_map(t_fdf *map)
{
	mlx_clear_window(map->p_mlx, map->p_win);
	map->img = mlx_new_image(map->p_mlx, 1000, 800);
	map->data.img = mlx_get_data_addr(map->img, &map->data.pixel_bits,
			&map->data.line_bytes, &map->data.endian);
	draw_backg(map, 0x181C26);
	trace_line(map);
	mlx_put_image_to_window(map->p_mlx, map->p_win, map->img, 0, 0);
	show_commands(map);
}

int command_pressed(int key, t_fdf *map)
{
    if (key == 65307)  // Escape key
    {
        mlx_destroy_window(map->p_mlx, map->p_win);
        exit(0);
    }
    if (key == 119)  // 'W' key - move up
        map->ver_move += 20;
    if (key == 115)  // 'S' key - move down
        map->ver_move -= 20;
    if (key == 97)   // 'A' key - move left
        map->hor_move += 20;
    if (key == 100)  // 'D' key - move right
        map->hor_move -= 20;
    if (key == 114)  // 'R' key - increase depth
        map->hor_view += 0.01;
    if (key == 102)  // 'F' key - decrease depth
        map->hor_view -= 0.01;

    draw_map(map);
    return (0);
}

int	main(int ac, char **av)
{
	t_fdf	*map;

	if (ac != 2)
		exit(-1);
	map = malloc(sizeof(t_fdf));
	if (!map)
		exit(-1);
	map->hor_view = 0.01;
	map->hor_move = 500;
	map->ver_move = 50;
	map->av = av;
	map->p_mlx = mlx_init();
	get_map(map);
	map->p_win = mlx_new_window(map->p_mlx, 1000, 800, av[1]);
	map->zoom = get_max(1000 / map->width, 2);
	draw_map(map);
	mlx_do_key_autorepeaton(map->p_mlx);
	mlx_hook(map->p_win, 2, (1L << 0), command_pressed, map);
	mlx_loop(map->p_mlx);
}