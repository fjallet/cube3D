/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:50:51 by fjallet           #+#    #+#             */
/*   Updated: 2023/03/19 13:03:46 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_data(t_arg *data)
{
	if (data->error_map == 3)
		return (printf("too many maps"), 1);
	if (check_file(data->no, ".xpm") || check_file(data->so, ".xpm") || \
	check_file(data->we, ".xpm") || check_file(data->ea, ".xpm"))
		return (printf("texture file\n"), 1);
	if (check_rgb(data->f) || check_rgb(data->c))
		return (printf("error : color rgb\n"), 1);
	if (data->error == 1)
		return (printf("More than one same texture\n"), 1);
	if (data->count_start == 0)
		return (printf("no starting point on the map\n"), 1);
	else if (data->count_start > 1)
		return (printf("too much starting points on the map\n"), 1);
	return (0);
}

int	check_argv(char *argv)
{
	int	fd;

	fd = open(argv, O_DIRECTORY);
	if (fd != -1)
		return (2);
	fd = 0;
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
		return (printf("missing file : "), 1);
	i = 0;
	while (str[i])
		i++;
	if (ft_strncmp(str + i - 4, suffix, 4) != 0)
	{
		printf("wrong file name : ");
		return (1);
	}
	if (check_argv(str) == 1)
	{
		printf("can't acces file : ");
		return (1);
	}
	if (check_argv(str) == 2)
	{
		printf("is not a file : ");
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
	if (!rgb)
		return (1);
	while (rgb[i])
	{
		if (rgb[i] == ',')
			i++;
		if (ft_atoi(&rgb[i]) > 255 || ft_atoi(&rgb[i]) < 0)
			return (1);
		if ((rgb[i] < 47 || rgb[i] > 58))
			return (1);
		while (rgb[i] > 47 && rgb[i] < 58)
			i++;
		count++;
	}
	if (count != 3)
		return (1);
	return (0);
}

int	check_line(char *str, t_arg *data)
{
	if (ft_ismap(str) == 0 && data->error_map == 0)
		data->error_map = 1;
	if (ft_ismap(str) && data->error_map == 1)
		data->error_map = 2;
	if (ft_ismap(str) == 0 && data->error_map == 2)
		data->error_map = 3;
	if (!str)
		return (0);
	if (!ft_strncmp(str, "NO", 2))
		return (get_path(data, &(data->no), str + 2));
	if (!ft_strncmp(str, "SO", 2))
		return (get_path(data, &(data->so), str + 2));
	if (!ft_strncmp(str, "WE", 2))
		return (get_path(data, &(data->we), str + 2));
	if (!ft_strncmp(str, "EA", 2))
		return (get_path(data, &(data->ea), str + 2));
	if (!ft_strncmp(str, "F", 1))
		return (get_shiet(data, &data->f, str + 1));
	if (!ft_strncmp(str, "C", 1))
		return (get_shiet(data, &data->c, str + 1));
	if (!ft_empty_sentence(str))
		return (0);
	data->map = get_map(str, data->map, data);
	return (0);
}
