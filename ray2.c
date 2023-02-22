/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:26:58 by fjallet           #+#    #+#             */
/*   Updated: 2023/02/21 14:42:07 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// calcule la taille des murs à imprimer
void	wall_size(t_fdf *f)
{
	f->lineheight = (int)(SCREENHEIGHT / f->perpwalldist);
	f->drawstart = -f->lineheight / 2 + SCREENHEIGHT / 2;
	if (f->drawstart < 0)
		f->drawstart = 0;
	f->drawend = f->lineheight / 2 + SCREENHEIGHT / 2;
	if (f->drawend >= SCREENHEIGHT)
		f->drawend = SCREENHEIGHT - 1;
}

//calculate value of wallX
//where exactly the wall was hit
//x coordinate on the texture
void	choose_text(t_fdf *f)
{
	double	wallx;

	if (f->side == 0 && f->raydirx < 0)
		f->texnum = 0;
	if (f->side == 0 && f->raydirx >= 0)
		f->texnum = 1;
	if (f->side == 1 && f->raydiry < 0)
		f->texnum = 2;
	if (f->side == 1 && f->raydiry >= 0)
		f->texnum = 3;
	if (f->side == 0)
		wallx = f->posy + f->perpwalldist * f->raydiry;
	else
		wallx = f->posx + f->perpwalldist * f->raydirx;
	wallx -= floor(wallx);
	f->texx = (int)(wallx * (double)TEXWIDTH);
	if (f->side == 0 && f->raydirx > 0)
		f->texx = TEXWIDTH - f->texx - 1;
	if (f->side == 1 && f->raydiry < 0)
		f->texx = TEXWIDTH - f->texx - 1;
}

// How much to increase the texture coordinate per screen pixel
// Starting texture coordinate
// Cast the texture coordinate to integer, and mask with (TEXHEIGHT - 1) 
//in case of overflow
// printf("y == %d et x == %d\n", y, x);
// printf("TEXHEIGHT * f->texx + f->texy == %d\n", 
//(TEXHEIGHT * f->texx + f->texy));
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

	y = f->drawstart;
	step = 1.0 * TEXHEIGHT / f->lineheight;
	texpos = (f->drawstart - SCREENHEIGHT / 2 + f->lineheight / 2) * step;
	while (y < f->drawend)
	{
		f->texy = (int)texpos & (TEXHEIGHT - 1);
		texpos += step;
		f->color = texture[f->texnum][TEXHEIGHT * f->texx + f->texy];
		draw_pixel(f, x, y, f->color);
		y++;
	}
}
