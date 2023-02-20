/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:50:51 by fjallet           #+#    #+#             */
/*   Updated: 2023/02/20 10:03:47 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_data(t_arg *data)
{
	if (check_file(data->no, ".xpm") || check_file(data->so, ".xpm") || \
	check_file(data->we, ".xpm") || check_file(data->ea, ".xpm"))
	{
		printf("texture file\n");
		return (1);
	}
	if (check_rgb(data->f) || check_rgb(data->c))
	{
		printf("floor and ceiling : wrong syntax\n");
		return (1);
	}
	if (data->count_start == 0)
	{
		printf("no starting point on the map\n");
		return (1);
	}
	else if (data->count_start > 1)
	{
		printf("too much starting points on the map\n");
		return (1);
	}
	return (0);
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

int	check_file(char *str, char *suffix)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
		i++;
	if (ft_strncmp(str + i - 4, suffix, 4) != 0)
	{
		printf("wrong file name : ");
		return (1);
	}
	if (check_argv(str))
	{
		printf("can't acces file : ");
		return (1);
	}
	return (0);
}

int	check_rgb(char *rgb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i == 0 || rgb[i] == ',')
	{
		if (rgb[i] == ',')
			i++;
		if (ft_atoi(rgb) > 255 && ft_atoi(rgb) > -1)
			return (1);
		while (rgb[i] > 47 && rgb[i] < 58)
			i++;
		count++;
	}
	if (count != 3)
		return (1);
	return (0);
}

void	check_line(char *str, t_arg *data)
{
	if (!str)
		return ;
	if (!ft_strncmp(str, "NO", 1))
		data->no = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "SO", 2))
		data->so = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "WE", 2))
		data->we = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "EA", 2))
		data->ea = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "F", 1))
		data->f = ft_strdup(str + 2);
	else if (!ft_strncmp(str, "C", 1))
		data->c = ft_strdup(str + 2);
	else if (!ft_empty_sentence(str))
		return ;
	else
		data->map = get_map(str, data->map, data);
}
