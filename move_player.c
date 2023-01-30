/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:53:20 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/30 17:45:49 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_forward_back(t_fdf *f)
{
	if (f->forward == 1)
	{
		if (f->data.tab[(int)(f->posX + (f->dirX * f->
						movespeed * 2))][(int)f->posY] == 0)
			f->posX += f->dirX * f->movespeed;
		if (f->data.tab[(int)(f->posX)][(int)(f->posY +
					(f->dirY * f->movespeed * 2))] == 0)
			f->posY += f->dirY * f->movespeed;
	}
	if (f->back == 1)
	{
		if (f->data.tab[(int)(f->posX - (f->dirX * f->
						movespeed * 2))][(int)(f->posY)] == 0)
			f->posX -= f->dirX * f->movespeed;
		if (f->data.tab[(int)(f->posX)][(int)(f->posY -
					(f->dirY * f->movespeed * 2))] == 0)
			f->posY -= f->dirY * f->movespeed;
	}
}

void	ft_left_right(t_fdf *f)
{
	if (f->right == 1)
	{
		if (f->data.tab[(int)(f->posX + f->dirY *
					(f->movespeed * 2))][(int)f->posY] == 0)
			f->posX += f->dirY * f->movespeed;
		if (f->data.tab[(int)f->posX][(int)(f->posY -
					f->dirX *
					(f->movespeed * 2))] == 0)
			f->posY -= f->dirX * f->movespeed;
	}
	if (f->left == 1)
	{
		if (f->data.tab[(int)(f->posX - f->dirY *
					(f->movespeed * 2))][(int)f->posY] == 0)
			f->posX -= f->dirY * f->movespeed;
		if (f->data.tab[(int)f->posX][(int)(f->posY +
					f->dirX *
					(f->movespeed * 2))] == 0)
			f->posY += f->dirX * f->movespeed;
	}
}

void	ft_rotate_right_left(t_fdf *f)
{
	double oldplanx;
	double olddirX;

	oldplanx = f->planeX;
	olddirX = f->dirX;
	if (f->rotate_right == 1)
	{
		f->dirX = f->dirX * cos(-f->rotspeed / 2) -
			f->dirY * sin(-f->rotspeed / 2);
		f->dirY = olddirX * sin(-f->rotspeed / 2) +
			f->dirY * cos(-f->rotspeed / 2);
		f->planeX = f->planeX * cos(-f->rotspeed / 2)
			- f->planeY * sin(-f->rotspeed / 2);
		f->planeY = oldplanx * sin(-f->rotspeed / 2) +
			f->planeY * cos(-f->rotspeed / 2);
	}
	ft_rotate_left(f, olddirX);
}

void	ft_rotate_left(t_fdf *f, double olddirX)
{
	double oldplanex;

	if (f->rotate_left == 1)
	{
		olddirX = f->dirX;
		oldplanex = f->planeX;
		f->dirX = f->dirX * cos(f->rotspeed / 2) -
			f->dirY * sin(f->rotspeed / 2);
		f->dirY = olddirX * sin(f->rotspeed / 2) + f->
			dirY * cos(f->rotspeed / 2);
		f->planeX = f->planeX * cos(f->rotspeed / 2) -
			f->planeY * sin(f->rotspeed / 2);
		f->planeY = oldplanex * sin(f->rotspeed / 2) +
			f->planeY * cos(f->rotspeed / 2);
	}
}