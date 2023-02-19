/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:21:23 by fjallet           #+#    #+#             */
/*   Updated: 2023/02/19 18:09:11 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*check_str(char *str, t_arg *data)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str + i, "N", 1) || !ft_strncmp(str + i, "S", 1) \
			|| !ft_strncmp(str + i, "W", 1) || !ft_strncmp(str + i, "E", 1))
		{
			data->count_start++;
			data->dir_player = str[i];
			data->x = i + 1;
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
	while (data->size_map != 1 && old_map[i])
	{
		new_map[i] = ft_strdup2(old_map[i]);
		i++;
	}
	if (data->dir_player && !data->y)
		data->y = i;
	new_map[i] = ft_strdup2(str);
	new_map[++i] = '\0';
	i = -1;
	while (old_map && old_map[++i])
		free(old_map[i]);
	free(old_map);
	return (new_map);
}

/*char	**get_map(char *str, char **old_map, t_arg *data)
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
	{
		while (old_map[i++])
			new_map[i - 1] = ft_strdup2(old_map[i - 1]);
	}
	if (data->dir_player && !data->y)
		data->y = i;
	printf("%i\n", i);
	new_map[i] = ft_strdup2(str);
	new_map[++i] = '\0';
	i = -1;
	while(old_map && old_map[++i])
		free(old_map[i]);
	free(old_map);
	return (new_map);
}*/

int	ft_empty_sentence(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' && \
		str[i] != '\n' && str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

int	get_data(t_arg *data, char *av)
{
	char	*line;

	ft_bzero(data, sizeof(t_arg));
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
	if (check_data(data))
	{
		free_tab(data->map);
		free_data(data);
		return (1);
	}
	return (0);
}

int	get_xpm_img(t_fdf *fdf)
{
	int	largeur;
	int	hauteur;

	largeur = 1920;
	hauteur = 1080;
	fdf->text[1].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text1.xpm", \
	&largeur, &hauteur);
	fdf->text[1].data = mlx_get_data_addr(fdf->text[1].image, \
	&fdf->text[1].bpp, &fdf->text[1].size_l, &fdf->text[1].endian);
	fdf->text[2].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text3.xpm", \
	&largeur, &hauteur);
	fdf->text[2].data = mlx_get_data_addr(fdf->text[2].image, \
	&fdf->text[2].bpp, &fdf->text[2].size_l, &fdf->text[2].endian);
	fdf->text[3].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text2.xpm", \
	&largeur, &hauteur);
	fdf->text[3].data = mlx_get_data_addr(fdf->text[3].image, \
	&fdf->text[3].bpp, &fdf->text[3].size_l, &fdf->text[3].endian);
	fdf->text[4].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text4.xpm", \
	&largeur, &hauteur);
	fdf->text[4].data = mlx_get_data_addr(fdf->text[4].image, \
	&fdf->text[4].bpp, &fdf->text[4].size_l, &fdf->text[4].endian);
	return (0);
}
