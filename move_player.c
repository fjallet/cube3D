/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:53:20 by abouleau          #+#    #+#             */
/*   Updated: 2023/02/19 18:54:23 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_forward_back(t_fdf *f)
{
	if (f->forward == 1)
	{
		if (f->data.tab[(int)(f->posx + (f->dirx * \
		f->movespeed * 2))][(int)f->posy] == 0)
			f->posx += f->dirx * f->movespeed;
		if (f->data.tab[(int)(f->posx)][(int)(f->posy + \
		(f->diry * f->movespeed * 2))] == 0)
			f->posy += f->diry * f->movespeed;
	}
	if (f->back == 1)
	{
		if (f->data.tab[(int)(f->posx - (f->dirx * \
		f->movespeed * 2))][(int)(f->posy)] == 0)
			f->posx -= f->dirx * f->movespeed;
		if (f->data.tab[(int)(f->posx)][(int)(f->posy - \
		(f->diry * f->movespeed * 2))] == 0)
			f->posy -= f->diry * f->movespeed;
	}
}

void	ft_left_right(t_fdf *f)
{
	if (f->right == 1)
	{
		if (f->data.tab[(int)(f->posx + f->diry * \
		(f->movespeed * 2))][(int)f->posy] == 0)
			f->posx += f->diry * f->movespeed;
		if (f->data.tab[(int)f->posx][(int)(f->posy - \
		f->dirx * (f->movespeed * 2))] == 0)
			f->posy -= f->dirx * f->movespeed;
	}
	if (f->left == 1)
	{
		if (f->data.tab[(int)(f->posx - f->diry * \
		(f->movespeed * 2))][(int)f->posy] == 0)
		f->posx -= f->diry * f->movespeed;
		if (f->data.tab[(int)f->posx][(int)(f->posy + \
		f->dirx * (f->movespeed * 2))] == 0)
			f->posy += f->dirx * f->movespeed;
	}
}

void	ft_rotate_right_left(t_fdf *f)
{
	double	oldplanx;
	double	olddirx;

	oldplanx = f->planex;
	olddirx = f->dirx;
	if (f->rotate_right == 1)
	{
		f->dirx = f->dirx * cos(-f->rotspeed / 2) - \
		f->diry * sin(-f->rotspeed / 2);
		f->diry = olddirx * sin(-f->rotspeed / 2) + \
		f->diry * cos(-f->rotspeed / 2);
		f->planex = f->planex * cos(-f->rotspeed / 2) - \
		f->planey * sin(-f->rotspeed / 2);
		f->planey = oldplanx * sin(-f->rotspeed / 2) + \
		f->planey * cos(-f->rotspeed / 2);
	}
	ft_rotate_left(f, olddirx);
}

void	ft_rotate_left(t_fdf *f, double olddirx)
{
	double	oldplanex;

	if (f->rotate_left == 1)
	{
		olddirx = f->dirx;
		oldplanex = f->planex;
		f->dirx = f->dirx * cos(f->rotspeed / 2) - \
		f->diry * sin(f->rotspeed / 2);
		f->diry = olddirx * sin(f->rotspeed / 2) + \
		f->diry * cos(f->rotspeed / 2);
		f->planex = f->planex * cos(f->rotspeed / 2) - \
		f->planey * sin(f->rotspeed / 2);
		f->planey = oldplanex * sin(f->rotspeed / 2) + \
		f->planey * cos(f->rotspeed / 2);
	}
}
