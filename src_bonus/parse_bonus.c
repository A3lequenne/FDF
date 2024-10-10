#include "fdf_bonus.h"

int	get_map_width(t_fdf *map)
{
	int		fd;
	char	**str_tab;
	int		i;
	char	*next_line;

	fd = open(map->av[1], O_RDONLY, 0777);
	if (fd == -1)
		exit(-1);
	next_line = get_next_line(fd);
	str_tab = ft_split(next_line, ' ');
	i = 0;
	if (str_tab == NULL)
		exit(-1);
	while (str_tab[i])
		i++;
	free_tab(str_tab);
	free(next_line);
	close(fd);
	return (i);
}

int	get_map_height(t_fdf *map)
{
	int		fd;
	char	*next_line;
	int		i;

	fd = open(map->av[1], O_RDONLY, 0777);
	i = 0;
    next_line = get_next_line(fd);
	while (next_line)
	{
		i++;
		free(next_line);
		next_line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	**malloc_map(t_fdf *map)
{
	int	**res;
	int	i;

	map->width = get_map_width(map);
	map->height = get_map_height(map);
	res = malloc(sizeof(int *) * map->height);
	if (!res)
		exit(-1);
	i = 0;
	while (i < map->height)
	{
		res[i] = malloc(sizeof(int) * map->width);
		if (!res[i])
			exit(-1);
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	sum;
	int	sign;
	int	found;

	sum = 0;
	sign = 1;
	found = 1;
	if (!str)
		exit(-1);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sign * sum);
}

void	get_map(t_fdf *map)
{
	char	*str;
	char	**str_tab;
	int		fd;
	int		j;
	int		i;

	map->map_tab = malloc_map(map);
	fd = open(map->av[1], O_RDONLY);
	str = get_next_line(fd);
	j = 0;
	while (str)
	{
		str_tab = ft_split(str, ' ');
		i = 0;
		while (i < map->width)
		{
			map->map_tab[j][i] = ft_atoi(str_tab[i]);
			i++;
		}
		free(str);
		free_tab(str_tab);
		str = get_next_line(fd);
		j++;
	}
	close(fd);
}