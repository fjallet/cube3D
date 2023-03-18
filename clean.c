/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:57:43 by abouleau          #+#    #+#             */
/*   Updated: 2023/03/18 17:24:29 by fjallet          ###   ########.fr       */
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
	if (!tab)
		return ;
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

void	free_data(t_arg *data)
{
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->no)
		free(data->no);
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
}
