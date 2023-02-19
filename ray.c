/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:43:55 by abouleau          #+#    #+#             */
/*   Updated: 2023/02/19 18:59:09 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// direction de la caméra
//x-coordinate in camera space
void	ray_screen(t_fdf *f, int x)
{
	f->camerax = 2 * x / (double)SCREENWIDTH - 1;
	f->raydirx = f->dirx + f->planex * f->camerax;
	f->raydiry = f->diry + f->planey * f->camerax;
}

// distance entre un carré et l'autre (pour les x et y)
void	ray_delta_step(t_fdf *f)
{
	if (f->raydirx <= 0.00001 && f->raydirx >= -0.00001)
		f->deltadistx = 1e30;
	else
		f->deltadistx = fabs(1.0 / f->raydirx);
	if (f->raydiry <= 0.00001 && f->raydiry >= -0.00001)
		f->deltadisty = 1e30;
	else
		f->deltadisty = fabs(1.0 / f->raydiry);
}

// distance entre la position initiale et le premier carré (en x et y)
// en prenant en compte la direction
void	first_step_direction(t_fdf *f)
{
	if (f->raydirx < 0)
	{
		f->stepx = -1;
		f->sidedistx = (f->posx - f->mapx) * f->deltadistx;
	}
	else
	{
		f->stepx = 1;
		f->sidedistx = (f->mapx + 1.0 - f->posx) * f->deltadistx;
	}
	if (f->raydiry < 0)
	{
		f->stepy = -1;
		f->sidedisty = (f->posy - f->mapy) * f->deltadisty;
	}
	else
	{
		f->stepy = 1;
		f->sidedisty = (f->mapy + 1.0 - f->posy) * f->deltadisty;
	}
}

// check si un mur est touché, et calcule la distance de ce dernier 
//avec le joueur
//jump to next map square, either in x-direction, or in y-direction
// Check if ray has hit a wall
// side indique si le mur est un x ou y;
void	check_wall_hit(t_fdf *f)
{
	while (f->hit == 0)
	{
		if (f->sidedistx < f->sidedisty)
		{
			f->sidedistx += f->deltadistx;
			f->mapx += f->stepx;
			f->side = 0;
		}
		else
		{
			f->sidedisty += f->deltadisty;
			f->mapy += f->stepy;
			f->side = 1;
		}
		if (f->data.tab[f->mapx][f->mapy] > 0)
			f->hit = 1;
	}
}

// calcule la distance entre le joueur et le premier mur touché
/*(f->sidedistx - f->deltadistx); */
/*(f->sidedisty - f->deltadisty);*/
void	ray_size(t_fdf *f)
{
	if (f->side == 0)
		f->perpwalldist = ((double) f->mapx - f->posx + \
		(1 - (double) f->stepx) / 2) / f->raydirx;
	else
		f->perpwalldist = ((double) f->mapy - f->posy + \
		(1 - (double) f->stepy) / 2) / f->raydiry;
}
