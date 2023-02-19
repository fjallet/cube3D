/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:38:19 by fjallet           #+#    #+#             */
/*   Updated: 2023/02/19 18:07:13 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	test_map(int i, int j, t_arg *data)
{
	if (data->map[i][j] == '0')
	{
		if (!data->map[i - 1][j] || !data->map[i + 1][j] || \
		!data->map[i][j - 1] || !data->map[i][j + 1])
			return (1);
		if ((data->map[i - 1][j] && data->map[i - 1][j] == ' ') || \
		(data->map[i + 1][j] && data->map[i + 1][j] == ' ') || \
		(data->map[i][j - 1] && data->map[i][j - 1] == ' ') || \
		(data->map[i][j + 1] && data->map[i][j + 1] == ' ') || \
		(data->map[i - 1][j - 1] && data->map[i - 1][j - 1] == ' ') || \
		(data->map[i + 1][j + 1] && data->map[i + 1][j + 1] == ' ') || \
		(data->map[i - 1][j + 1] && data->map[i - 1][j + 1] == ' ') || \
		(data->map[i + 1][j - 1] && data->map[i + 1][j - 1] == ' '))
			return (1);
	}
	else if (data->map[i][j] != ' ' && data->map[i][j] != '1')
		return (1);
	return (0);
}

int	map_parsing2(t_arg *data, int i, int j)
{
	if (j < ft_strlen2(data->map[i]) && test_map(i, j, data))
	{
		printf("wrong map\n");
		free_coord(data->tab, data->size_map);
		return (1);
	}
	if (j >= ft_strlen2(data->map[i]) || data->map[i][j] == ' ' || \
	data->map[i][j] == '1')
		data->tab[i][j] = 1;
	else
		data->tab[i][j] = 0;
	return (0);
}

int	map_parsing(t_arg *data)
{
	int	i;
	int	j;

	i = 0;
	if (create_int_tab(data))
		return (1);
	while (i < data->size_map)
	{
		j = 0;
		while (j < data->longest_line)
		{
			if (map_parsing2(data, i, j))
				return (1);
			j++;
		}
		i++;
	}
	free_tab(data->map);
	return (0);
}

int	create_trgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	get_rgb(char *rgb, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i == 0 || rgb[i] == ',')
	{
		if (rgb[i] == ',')
			i++;
		if (count == c)
			return (ft_atoi(&rgb[i]));
		while (rgb[i] > 47 && rgb[i] < 58)
			i++;
		count++;
	}
	return (0);
}
