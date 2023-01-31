/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:36:28 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/31 16:55:19 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_fdf *fdf, int x1, int y1, int color)
{
	char	*dst;

	if (y1 >= screenHeight || x1 >= screenWidth || x1 < 0 || y1 < 0)
		return ;
	dst = fdf->text[0].data + (y1 * fdf->text[0].size_l) + x1 * \
	(fdf->text[0].bpp / 8);
	*(unsigned int *)dst = color;
}

int	get_color(int x, int y, t_text text)
{
	int	color;

	color = (*(int *)(text.data + (y * text.size_l + (x * (text.bpp / 8)))));
	return (color);
}

void	ft_draw_ceillings_floors(t_fdf *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth && y >= (screenHeight / 2))
		{
			draw_pixel(f, x, y, f->floor);
			x++;
		}
		while (x < screenWidth && y < (screenHeight / 2))
		{
			draw_pixel(f, x, y, f->ceiling);
			x++;
		}
		y++;
	}
}
