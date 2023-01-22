/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:43:55 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/21 11:27:43 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ray_screen(t_fdf *f, int x) // direction de la caméra
{
	f->cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
    f->rayDirX = f->dirX + f->planeX * f->cameraX;
    f->rayDirY = f->dirY + f->planeY * f->cameraX;
}

void	ray_delta_step(t_fdf *f) // distance entre un carré et l'autre (pour les x et y)
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

void	first_step_direction(t_fdf *f) // distance entre la position initiale et le premier carré (en x et y)
{                                      // en prenant en compte la direction
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

void    check_wall_hit(t_fdf *f) // check si un mur est touché, et calcule la distance de ce dernier avec le joueur
{
    while (f->hit == 0)
    { //jump to next map square, either in x-direction, or in y-direction
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
        if (worldMap[f->mapX][f->mapY] > 0) // Check if ray has hit a wall
            f->hit = 1;
    }
    // side indique si le mur est un x ou y;
}

void ray_size(t_fdf *f) // calcule la distance entre le joueur et le premier mur touché
{
    if(f->side == 0)
		f->perpWallDist = /*(f->sideDistX - f->deltaDistX); */((double) f->mapX - f->posX + (1 - (double) f->stepX) / 2) / f->rayDirX;
    else
		f->perpWallDist = /*(f->sideDistY - f->deltaDistY);*/((double) f->mapY - f->posY + (1 - (double) f->stepY) / 2) / f->rayDirY;
}

void    wall_size(t_fdf *f) // calcule la taille des murs à imprimer
{
    f->lineHeight = (int)(screenHeight / f->perpWallDist);
	f->drawStart = -f->lineHeight / 2 + screenHeight / 2;
	if(f->drawStart < 0)
		f->drawStart = 0;
	f->drawEnd = f->lineHeight / 2 + screenHeight / 2;
	if(f->drawEnd >= screenHeight)
		f->drawEnd = screenHeight - 1;
}

void    choose_text(t_fdf *f)
{
	if (f->side == 0 && f->rayDirX < 0)
		f->texNum = 0;
	if (f->side == 0 && f->rayDirX >= 0)
		f->texNum = 1;
	if (f->side == 1 && f->rayDirY < 0)
		f->texNum = 2;
	if (f->side == 1 && f->rayDirY >= 0)
		f->texNum = 3;
			//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (f->side == 0) 
		wallX = f->posY + f->perpWallDist * f->rayDirY;
	else
		wallX = f->posX + f->perpWallDist * f->rayDirX;
	wallX -= floor(wallX);
	//x coordinate on the texture
    f->texX = (int)(wallX * (double)texWidth);
    if(f->side == 0 && f->rayDirX > 0) 
		f->texX = texWidth - f->texX - 1;
    if(f->side == 1 && f->rayDirY < 0)
		f->texX = texWidth - f->texX - 1;
}

void    ft_draw_walls(t_fdf *f, long long **buffer, int x, long long **texture)
{
    // How much to increase the texture coordinate per screen pixel
	double step = 1.0 * texHeight / f->lineHeight;
	// Starting texture coordinate
	double texPos = (f->drawStart - screenWidth / 2 + f->lineHeight / 2) * step;
	for(int y = f->drawStart ; y < f->drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		f->texY = (int)texPos & (texHeight - 1);
		texPos += step;
		f->color = texture[f->texNum][texHeight * f->texX + f->texY];
		// printf("y == %d et x == %d\n", y, x);
		// printf("texHeight * f->texX + f->texY == %d\n", (texHeight * f->texX + f->texY));
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	    /*if(f->side == 1) 
			f->color = (f->color >> 1) & 8355711; // permet de choisir quelle texture utiliser ?*/
		draw_pixel(f, x, y, f->color);
		//buffer[y][x] = f->color;
		(void)buffer;
	}
}
