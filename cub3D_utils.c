/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:04:41 by fjallet           #+#    #+#             */
/*   Updated: 2023/02/19 18:29:22 by fjallet          ###   ########.fr       */
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

char	*ft_strdup2(const char *s)
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
}

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