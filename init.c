/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:49:51 by abouleau          #+#    #+#             */
/*   Updated: 2023/02/19 18:56:14 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_texture(t_fdf *f)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = -1;
	f->texture = malloc (sizeof(long long) * 4);
	if (!(f->texture))
		return (1);
	while (i < 4)
		f->texture[i++] = malloc (sizeof(long long) * (TEXWIDTH * TEXHEIGHT));
	if (!f->texture)
		return (1);
	while (++x < TEXWIDTH)
	{
		y = -1;
		while (++y < TEXHEIGHT)
		{
			f->texture[0][TEXWIDTH * y + x] = get_color(x, y, f->text[1]);
			f->texture[1][TEXWIDTH * y + x] = get_color(x, y, f->text[2]);
			f->texture[2][TEXWIDTH * y + x] = get_color(x, y, f->text[3]);
			f->texture[3][TEXWIDTH * y + x] = get_color(x, y, f->text[4]);
		}
	}
	return (0);
}

void	start_pos_init_ns(t_fdf *f, char c)
{
	if (c == 'N')
	{
		f->dirx = -1;
		f->diry = 0;
		f->planex = 0;
		f->planey = 0.66;
	}
	if (c == 'S')
	{
		f->dirx = 1;
		f->diry = 0;
		f->planex = 0;
		f->planey = -0.66;
	}
}

void	start_pos_init_we(t_fdf *f, char c)
{
	if (c == 'W')
	{
		f->dirx = 0;
		f->diry = -1;
		f->planex = -0.66;
		f->planey = 0;
	}
	if (c == 'E')
	{
		f->dirx = 0;
		f->diry = 1;
		f->planex = 0.66;
		f->planey = 0;
	}
}

int	cube3d_init(t_fdf *f, char *av)
{
	if (get_data(&f->data, av))
		return (1);
	if (map_parsing(&f->data))
		return (1);
	f->movespeed = 0.00003;
	f->rotspeed = 0.00003;
	f->posx = f->data.y;
	f->posy = f->data.x;
	f->mapwidth = f->data.longest_line;
	f->mapheight = f->data.size_map;
	start_pos_init_ns(f, f->data.dir_player);
	start_pos_init_we(f, f->data.dir_player);
	f->floor = create_trgb(get_rgb(f->data.f, 0), get_rgb(f->data.f, 1), \
	get_rgb(f->data.f, 2));
	f->ceiling = create_trgb(get_rgb(f->data.c, 0), get_rgb(f->data.c, 1), \
	get_rgb(f->data.c, 2));
	return (0);
}

int	img_init(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, SCREENWIDTH, SCREENHEIGHT, \
	"Cub3D");
	fdf->text[0].image = mlx_new_image(fdf->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	fdf->text[0].data = mlx_get_data_addr(fdf->text[0].image, \
	&fdf->text[0].bpp, &fdf->text[0].size_l, &fdf->text[0].endian);
	if (get_xpm_img(fdf))
		return (1);
	get_texture(fdf);
	(void)fdf;
	return (0);
}
