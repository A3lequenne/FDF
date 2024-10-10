#include "fdf.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	get_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

int	get_abs(int nb)
{
	if (0 > nb)
		return (-nb);
	return (nb);
}