/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:38:19 by fjallet           #+#    #+#             */
/*   Updated: 2023/01/22 19:16:01 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strlen2(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while(str[i])
		i++;
	return (i);
}

int	create_int_tab(t_arg *data)
{
	int	i;

	i = 0;
	data->tab = (int **) malloc (sizeof(int *) * (data->size_map + 1));
	if (!(data->tab))
		return (1);
	while (i < data->size_map)
	{
		data->tab[i] = (int *) malloc (sizeof(int) * (data->longest_line));
		if (!(data->tab[i]))
		{
			while (i-- > 0)
				free(data->tab[i]);
			free(data->tab);
			return (1);
		}
		i++;
	}
	data->tab[i] = NULL;
	return(0);
}

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
			if (j < ft_strlen2(data->map[i]) && test_map(i, j, data))
			{
				printf("wrong map\n");
				free_coord(data->tab, data->size_map);
				return (1);
			}
			if (j >= ft_strlen2(data->map[i]) || data->map[i][j] == ' ' ||\
			 data->map[i][j] == '1')
				data->tab[i][j] = 1;
			else
				data->tab[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}
