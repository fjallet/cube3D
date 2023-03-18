/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:04:41 by fjallet           #+#    #+#             */
/*   Updated: 2023/03/18 19:20:43 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strlen2(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
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
	return (0);
}

/*char	*ft_strdup2(const char *s)
{
	size_t	len;
	size_t	i;
	char	*tab;

	i = 0;
	len = ft_strlen(s);
	tab = (char *) malloc (sizeof(char) * (len + 1));
	if (!tab)
		return (0);
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}*/

/*char	*ft_put_rgb_to_hex(char *rgb, char *hex)
{
	char	*base;
	int		i;
	int		j;

	i = 0;
	j = 0;
	base = "0123456789ABCDEF";
	while (i < ft_strlen(rgb))
	{
		if (i == 0 || rgb[i - 1] == ',')
		{
			hex[j++] = base[ft_atoi(rgb) / 16]
			hex[j++] = base[ft_atoi(rgb) % 16]
			if (j == 6)
				break ;
		}
		i++;
	}
	return (hex);
}*/

int	get_path(t_arg *data, char **text, char *str)
{
	int	i;

	i = 0;
	if (*text)
	{
		data->error = 1;
		return (1);
	}
	while (str[i] == ' ')
		i++;
	*text = ft_strdup(&str[i]);
	return (0);
}

int	get_shiet(t_arg *data, char **rgb, char *str)
{
	int	i;

	i = 0;
	if (*rgb)
	{
		data->error = 1;
		return (1);
	}
	while (str[i] == ' ')
		i++;
	*rgb = ft_strdup(&str[i]);
	return (0);
}

int	ft_ismap(char *str)
{
	int	i;

	i = 0;
	if (!ft_empty_sentence(str))
		return (0) ;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' &&\
		str[i] != 'S' && str[i] != 'N' && str[i] != 'E' && str[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}