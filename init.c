/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:49:51 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/31 16:12:17 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strdup2(const char *s)
{
	size_t	len;
	size_t	i;
	char	*tab;

	i = 0;
	len = ft_strlen(s);
	tab = (char *) malloc (sizeof(char) * (len + 1));
	if (!tab)
		return (0);
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

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
		f->texture[i++] = malloc (sizeof(long long) * (texWidth * texHeight));
	if (!f->texture)
		return (1);
	while (++x < texWidth)
	{
		y = -1;
		while (++y < texHeight)
		{
			f->texture[0][texWidth * y + x] = get_color(x, y, f->text[1]);
			f->texture[1][texWidth * y + x] = get_color(x, y, f->text[2]);
			f->texture[2][texWidth * y + x] = get_color(x, y, f->text[3]);
			f->texture[3][texWidth * y + x] = get_color(x, y, f->text[4]);
		}
	}
	return (0);
}

void	start_pos_init(t_fdf *f, char c)
{
	if (c == 'N')
	{
		f->dirX = -1;
		f->dirY = 0;
		f->planeX = 0;
		f->planeY = 0.66;
	}
	if (c == 'S')
	{
		f->dirX = 1;
		f->dirY = 0;
		f->planeX = 0;
		f->planeY = -0.66;
	}
	if (c == 'W')
	{
		f->dirX = 0;
		f->dirY = -1;
		f->planeX = -0.66;
		f->planeY = 0;
	}
	if (c == 'E')
	{
		f->dirX = 0;
		f->dirY = 1;
		f->planeX = 0.66;
		f->planeY = 0;
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
	f->posX = f->data.y;
	f->posY = f->data.x;
	f->mapWidth = f->data.longest_line;
	f->mapHeight = f->data.size_map;
	start_pos_init(f, f->data.dir_player);
	f->floor = create_trgb(get_rgb(f->data.f, 0), get_rgb(f->data.f, 1), \
	get_rgb(f->data.f, 2));
	f->ceiling = create_trgb(get_rgb(f->data.c, 0), get_rgb(f->data.c, 1), \
	get_rgb(f->data.c, 2));
	return (0);
}

int	img_init(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, screenWidth, screenHeight, \
	"Cub3D");
	fdf->text[0].image = mlx_new_image(fdf->mlx_ptr, screenWidth, screenHeight);
	fdf->text[0].data = mlx_get_data_addr(fdf->text[0].image, \
	&fdf->text[0].bpp, &fdf->text[0].size_l, &fdf->text[0].endian);
	if (get_xpm_img(fdf))
		return (1);
	get_texture(fdf);
	(void)fdf;
	return (0);
}
