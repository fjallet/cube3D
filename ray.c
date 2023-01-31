/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:43:55 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/31 16:34:24 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// direction de la caméra
//x-coordinate in camera space
void	ray_screen(t_fdf *f, int x)
{
	f->cameraX = 2 * x / (double)screenWidth - 1;
	f->rayDirX = f->dirX + f->planeX * f->cameraX;
	f->rayDirY = f->dirY + f->planeY * f->cameraX;
}

// distance entre un carré et l'autre (pour les x et y)
void	ray_delta_step(t_fdf *f)
{
	if (f->rayDirX <= 0.00001 && f->rayDirX >= -0.00001)
		f->deltaDistX = 1e30;
	else
		f->deltaDistX = fabs(1.0 / f->rayDirX);
	if (f->rayDirY <= 0.00001 && f->rayDirY >= -0.00001)
		f->deltaDistY = 1e30;
	else
		f->deltaDistY = fabs(1.0 / f->rayDirY);
}

// distance entre la position initiale et le premier carré (en x et y)
// en prenant en compte la direction
void	first_step_direction(t_fdf *f)
{
	if (f->rayDirX < 0)
	{
		f->stepX = -1;
		f->sideDistX = (f->posX - f->mapX) * f->deltaDistX;
	}
	else
	{
		f->stepX = 1;
		f->sideDistX = (f->mapX + 1.0 - f->posX) * f->deltaDistX;
	}
	if (f->rayDirY < 0)
	{
		f->stepY = -1;
		f->sideDistY = (f->posY - f->mapY) * f->deltaDistY;
	}
	else
	{
		f->stepY = 1;
		f->sideDistY = (f->mapY + 1.0 - f->posY) * f->deltaDistY;
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
		if (f->sideDistX < f->sideDistY)
		{
			f->sideDistX += f->deltaDistX;
			f->mapX += f->stepX;
			f->side = 0;
		}
		else
		{
			f->sideDistY += f->deltaDistY;
			f->mapY += f->stepY;
			f->side = 1;
		}
		if (f->data.tab[f->mapX][f->mapY] > 0)
			f->hit = 1;
	}
}

// calcule la distance entre le joueur et le premier mur touché
/*(f->sideDistX - f->deltaDistX); */
/*(f->sideDistY - f->deltaDistY);*/
void	ray_size(t_fdf *f)
{
	if (f->side == 0)
		f->perpWallDist = ((double) f->mapX - f->posX + \
		(1 - (double) f->stepX) / 2) / f->rayDirX;
	else
		f->perpWallDist = ((double) f->mapY - f->posY + \
		(1 - (double) f->stepY) / 2) / f->rayDirY;
}
