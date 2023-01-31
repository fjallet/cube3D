/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:26:58 by fjallet           #+#    #+#             */
/*   Updated: 2023/01/31 16:40:16 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// calcule la taille des murs à imprimer
void	wall_size(t_fdf *f)
{
	f->lineHeight = (int)(screenHeight / f->perpWallDist);
	f->drawStart = -f->lineHeight / 2 + screenHeight / 2;
	if (f->drawStart < 0)
		f->drawStart = 0;
	f->drawEnd = f->lineHeight / 2 + screenHeight / 2;
	if (f->drawEnd >= screenHeight)
		f->drawEnd = screenHeight - 1;
}

//calculate value of wallX
//where exactly the wall was hit
//x coordinate on the texture
void	choose_text(t_fdf *f)
{
	double	wallx;

	if (f->side == 0 && f->rayDirX < 0)
		f->texNum = 0;
	if (f->side == 0 && f->rayDirX >= 0)
		f->texNum = 1;
	if (f->side == 1 && f->rayDirY < 0)
		f->texNum = 2;
	if (f->side == 1 && f->rayDirY >= 0)
		f->texNum = 3;
	if (f->side == 0)
		wallx = f->posY + f->perpWallDist * f->rayDirY;
	else
		wallx = f->posX + f->perpWallDist * f->rayDirX;
	wallx -= floor(wallx);
	f->texX = (int)(wallx * (double)texWidth);
	if (f->side == 0 && f->rayDirX > 0)
		f->texX = texWidth - f->texX - 1;
	if (f->side == 1 && f->rayDirY < 0)
		f->texX = texWidth - f->texX - 1;
}

// How much to increase the texture coordinate per screen pixel
// Starting texture coordinate
// Cast the texture coordinate to integer, and mask with (texHeight - 1) 
//in case of overflow
// printf("y == %d et x == %d\n", y, x);
// printf("texHeight * f->texX + f->texY == %d\n", 
//(texHeight * f->texX + f->texY));
//make color darker for y-sides: R, G and B byte each divided through 
//two with a "shift" and an "and"
/*if(f->side == 1) 
f->color = (f->color >> 1) & 8355711; 
// permet de choisir quelle texture utiliser ?*/
void	ft_draw_walls(t_fdf *f, int x, long long **texture)
{
	double	step;
	double	texpos;
	int		y;

	y = f->drawStart;
	step = 1.0 * texHeight / f->lineHeight;
	texpos = (f->drawStart - screenWidth / 2 + f->lineHeight / 2) * step;
	while (y < f->drawEnd)
	{
		f->texY = (int)texpos & (texHeight - 1);
		texpos += step;
		f->color = texture[f->texNum][texHeight * f->texX + f->texY];
		draw_pixel(f, x, y, f->color);
		y++;
	}
}
