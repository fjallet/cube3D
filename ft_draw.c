/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:36:28 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/22 16:55:03 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_pixel(t_fdf *fdf, int x1, int y1, int color)
{
	char	*dst;
	
	if (y1 >= screenHeight || x1 >= screenWidth || x1 < 0 || y1 < 0)
		return ;
	dst = fdf->text[0].data + (y1 * fdf->text[0].size_l) + x1 * (fdf->text[0].bpp / 8);
	*(unsigned int *)dst = color;
	//fdf->text[0].data[index + 3] = (color & 0xFF000000) >> 24;
	//fdf->text[0].data[index + 2] = (color & 0x00FF0000) >> 16;
	//fdf->text[0].data[index + 1] = (color & 0x0000FF00) >> 8;
	//fdf->text[0].data[index] = color & 0x000000FF;
}

int	get_color(int x, int y, t_text text)
{
	int	color;

	color = (*(int *)(text.data + (y * text.size_l + (x * (text.bpp / 8)))));
	return (color);
}

void    ft_draw_ceillings_floors(t_fdf *f, long long **buffer, long long **texture)
{
		for(int y = 0; y < screenHeight; y++)
		{
			float rayDirX0 = f->dirX - f->planeX;
			float rayDirY0 = f->dirY - f->planeY;
			float rayDirX1 = f->dirX + f->planeX;
			float rayDirY1 = f->dirY + f->planeY;
			int p = y - screenHeight / 2;
			float posZ = 0.5 * screenHeight;
			float rowDistance = posZ / p;
			float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
			float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;
			float floorX = f->posX + rowDistance * rayDirX0;
			float floorY = f->posY + rowDistance * rayDirY0;

			for(int x = 0; x < screenWidth; ++x)
			{
				int cellX = (int)floorX;
				int cellY = (int)floorY;
				int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
				int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

				floorX += floorStepX;
				floorY += floorStepY;
				int floorTexture = 4;
				int ceilingTexture = 7;
				f->color = texture[floorTexture][texWidth * ty + tx];
				f->color = (f->color >> 1) & 8355711; // make a bit darker
				draw_pixel(f, x, y, f->color);
				//buffer[y][x] = f->color;
				f->color = texture[ceilingTexture][texWidth * ty + tx];
				f->color = (f->color >> 1) & 8355711; // make a bit darker
				draw_pixel(f, x, screenHeight - y - 1, f->color);
				//buffer[screenHeight - y - 1][x] = f->color;
			}
		}
		(void)buffer;
}

/*void    draw_raycasting(t_fdf *f, long long **buffer)
{
		int xo, yo;
	for(yo = 0; yo < screenHeight; yo++)
	{
		for(xo = 0; xo < screenWidth; xo++)
		{
			draw_pixel(f, xo, yo, buffer[yo][xo]);
		}
	}
}*/