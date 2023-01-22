/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:57:43 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/22 16:50:10 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*int	ft_close(t_fdf *param)
{
	if (param->mlx_ptr && param->image)
		mlx_destroy_image(param->mlx_ptr, param->image);
	if (param->mlx_ptr && param->win_ptr)
		mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	if (param->mlx_ptr)
		mlx_destroy_display(param->mlx_ptr);
	free(param->mlx_ptr);
	exit(0);
}*/

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_coord(int **map, int count_y)
{
	int	i;

	i = 0;
	while (i < count_y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	check_argv(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int	check_file(char *str)
{
	int	i;
	
	if (!str)
		return (1);
	i = 0;
	while (str[i])
		i++;
	if (ft_strncmp(str + i - 4, ".cub", 4) != 0)
		return (1);
	if (check_argv(str))
		return (1);
	return (0);
}
