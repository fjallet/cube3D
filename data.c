/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:21:23 by fjallet           #+#    #+#             */
/*   Updated: 2023/01/30 18:50:44 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*check_str(char *str, t_arg *data)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str + i, "N", 1) || !ft_strncmp(str + i, "S", 1) 
			|| !ft_strncmp(str + i, "W", 1) || !ft_strncmp(str + i, "E", 1))
		{
			data->count_start++;
			data->dir_player = str[i];
			data->x = i;
			str[i] = '0';
		}
	}
	if (i > data->longest_line)
		data->longest_line = i;
	return (str);
}

char	**get_map(char *str, char **old_map, t_arg *data)
{
	int		i;
	char	**new_map;

	if (!str)
		return (NULL);
	data->size_map++;
	new_map = (char **) malloc (sizeof(char *) * (data->size_map + 1));
	i = 0;
	str = check_str(str, data);
	if (data->size_map != 1)
		while (old_map[i])
		{
			new_map[i] = ft_strdup2(old_map[i]);
			i++;
		}
	if (data->dir_player && !data->y)
		data->y = i;
	new_map[i] = ft_strdup2(str);
	new_map[++i] = '\0';
	i = -1;
	if (old_map)
		while(old_map[++i])
			free(old_map[i]);
	free(old_map);
	return (new_map);
}

int	ft_empty_sentence(char *str)
{
	int i = 0;
	if (str[i] == '\n')
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
				&& str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

void	check_line(char *str, t_arg *data)
{
	if (!str)
		return ;
	if (!ft_strncmp(str, "NO", 1) && check_argv(str + 5) == 0)
		data->no = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "SO", 2) && check_argv(str + 5) == 0)
		data->so = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "WE", 2) && check_argv(str + 5) == 0)
		data->we = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "EA", 2) && check_argv(str + 5) == 0)
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

int	get_data(t_arg *data, char *av)
{
	char	*line;

	data->fd = open(av, O_RDONLY);
	line = get_next_line(data->fd);
	data->size_map = 0;
	data->longest_line = 0;
	data->count_start = 0;
	while (line)
	{
		if (line)
			check_line(line, data);
		free(line);
		line = get_next_line(data->fd);
	}
	return (0);
}