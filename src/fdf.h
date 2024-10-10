#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/get_next_line.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_img_data
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*img;
}	t_img_data;

typedef struct s_fdf
{
	t_img_data	data;
	float		x;
	float		y;
	void		*img;
	void		*p_mlx;
	void		*p_win;
	char		**av;
	int			height;
	int			width;
	int			**map_tab;
	float		zoom;
	int			hor_move;
	int			ver_move;
	float		hor_view;
}		t_fdf;

int		get_abs(int nb);
int		get_max(int n1, int n2);
void	free_tab(char **map);
void	put_pixel(t_fdf *map, int p_x, int p_y, int color);
void	get_map(t_fdf *map);
void	trace_line(t_fdf *map);

#endif