/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:59:22 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/26 23:43:03 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	draw_pixel(t_fdf *fdf, int x1, int y1)
// {
// 	size_t	index;
// 	// printf("??\n");
// 	if (y1 >= screenHeight || x1 >= screenWidth || x1 < 0 || y1 < 0)
// 		return ;
// 	index = (y1 * fdf->size_l) + x1 * (fdf->bpp / 8);
// 	fdf->data[index + 3] = (fdf->color & 0xFF000000) >> 24;
// 	fdf->data[index + 2] = (fdf->color & 0x00FF0000) >> 16;
// 	fdf->data[index + 1] = (fdf->color & 0x0000FF00) >> 8;
// 	fdf->data[index] = fdf->color & 0x000000FF;
// }

int	ft_abs(int value)
{
	if (value < 0)
		return (-1 * value);
	return (value);
}

void	draw_segment2(t_fdf *fdf, t_segment s, t_data_slope data)
{
	// printf("??\n");
	int i = 0;
	while (!(s.x1 == s.x2 && s.y1 == s.y2))
	{
		if (i < 5)
			// printf("s.x1 == %d, s.x2 == %d, s.y1 == %d, s.y2 == %d\n", s.x1, s.x2, s.y1, s.y2);
		i++;
		if (s.x1 < screenWidth && s.x1 > 0 && s.y1 < screenHeight && s.y1 > 0)
			draw_pixel(fdf, s.x1, s.y1);
		data.slope_director = 2 * data.slope_error;
		if (data.slope_director >= data.dy)
		{
			data.slope_error += data.dy;
			s.x1 += data.x_increment;
		}
		if (data.slope_director <= data.dx)
		{
			data.slope_error += data.dx;
			s.y1 += data.y_increment;
		}
	}
}

void	draw_segment(t_fdf *fdf, t_segment s)
{
	t_data_slope	data;

	data.dx = ft_abs(s.x2 - s.x1);
	data.dy = -ft_abs(s.y2 - s.y1);
	data.slope_director = 0;
	data.slope_error = data.dx + data.dy;
	data.x_increment = 0;
	data.y_increment = 0;
	if (s.x1 < s.x2)
		data.x_increment = 1;
	else
		data.x_increment = -1;
	if (s.y1 < s.y2)
		data.y_increment = 1;
	else
		data.y_increment = -1;
	// printf("??\n");
	draw_segment2(fdf, s, data);
}

/*t_segment	get_seg(int x, t_fdf *f)
{
	t_segment	s;

	int y = 5;
	s.x1 = f->px - x;
	s.y1 = f->py - y;
	s.x2 = f->px - x;
	s.y2 = f->py + y;
	return (s);
}*/

/*t_segment	get_seg2(int x, t_fdf *f)
{
	t_segment	s;

	int y = 5;
	s.x1 = f->px + x;
	s.y1 = f->py - y;
	s.x2 = f->px + x;
	s.y2 = f->py + y;
	return (s);
}*/

/*void	draw_dir(t_fdf *f)
{
	t_segment	s;

	s.x1 = f->px;
	s.y1 = f->py;
	s.x2 = f->px + f->pdx * 5;
	s.y2 = f->py + f->pdy * 5;
	draw_segment(f, s);
}

void	ft_draw_player(t_fdf *f)
{
	int	i;
	int	x;

	i = 0;
	x = 5;
	while (i < 5)
	{
		draw_segment(f, get_seg(x, f));
		i++;
		x--;
	}
	while (i < 10)
	{
		draw_segment(f, get_seg2(x, f));
		i++;
		x++;
	}
	draw_dir(f);
}*/

// void	ft_draw_coord(int x, int y, t_fdf *f)
// {
// 	t_segment	s;
// 	printf("x == %d et y == %d\n", x, y);
// 	s.x1 = x;
// 	s.y1 = x;
// 	s.x2 = y;
// 	s.y2 = y;
// 	draw_segment(f, s);
// }

void	ft_draw_coord(int xo, int yo, int mapS, t_fdf *f)
{
	t_segment	s;
	int max = xo + mapS - 1;
	s.y1 = yo + 1;
	s.y2 = yo + mapS - 1;
	while (xo < max)
	{
		s.x1 = xo + 1;
		s.x2 = xo + 1;
		draw_segment(f, s);
		xo++;
	}
}

void	draw_walls(t_fdf *f, t_segment s)
{
	f->color = 0xFF8000;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
}

void	draw_floors(t_fdf *f, t_segment s)
{
	f->color = 0x54e8fc;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
}

void	draw_ceillings(t_fdf *f, t_segment s)
{
	f->color = 0xd7e1e3;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
	s.x1 += 1;
	s.y1 = s.y1;
	s.x2 += 1;
	s.y2 = s.y2;
	draw_segment(f, s);
}