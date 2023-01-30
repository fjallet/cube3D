/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:04:41 by fjallet           #+#    #+#             */
/*   Updated: 2023/01/30 17:06:32 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	create_trgb(int r, int g , int b)
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