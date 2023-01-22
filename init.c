/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:49:51 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/22 19:08:02 by fjallet          ###   ########.fr       */
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

/*long long	**get_texture(t_fdf *f)
{
	long long **texture;
	texture = malloc (sizeof(long long) * 8);
	for(int i = 0; i < 8; i++)
		texture[i] = malloc (sizeof(long long) * (texWidth * texHeight));
	for(int x = 0; x < texWidth; x++)
	{
		for(int y = 0; y < texHeight; y++)
		{
			texture[0][texWidth * y + x] = get_color(x, y, f.text[1]);
			texture[1][texWidth * y + x] = get_color(x, y, f.text[2]);
			texture[2][texWidth * y + x] = get_color(x, y, f.text[3]);
			texture[3][texWidth * y + x] = get_color(x, y, f.text[4]);
			texture[4][texWidth * y + x] = 957410;//floor
			texture[7][texWidth * y + x] = 10186690; //ceilling
		}
	}
	return (texture);
}*/

/*int	get_floor(char *f)
{
	char	*rgb;
	int i = 0;
	rgb = malloc(sizeof(char) * (ft_strlen(f) - 2 + 1));
	while(f[i])
	{
		if(f[i] != ',')
			rgb[i] = f[i];
		i++;
	}
	//ft_print_unsignbr_base(ft_atoi(f));
}*/

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

int	cube3D_init(t_fdf *f, char *av)
{
	if (get_data(&f->data, av))
		return (1);
	if (map_parsing(&f->data))
		return (1);
	f->movespeed = 0.0001;
	f->rotspeed = 0.0001; //0.033 * 1.8;
	f->posX = f->data.x;
	f->posY = f->data.y;
	start_pos_init(f, f->data.dir_player);
	//fdf.floor = get_floor(fdf.data.f);
	return (0);
}

int	img_init(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, screenWidth, screenHeight, "Cub3D");
	fdf->text[0].image = mlx_new_image(fdf->mlx_ptr, screenWidth, screenHeight);
	fdf->text[0].data = mlx_get_data_addr(fdf->text[0].image, &fdf->text[0].bpp, &fdf->text[0].size_l, &fdf->text[0].endian);
	int largeur = 1920;
	int hauteur = 1080;
	fdf->text[1].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text1.xpm", &largeur, &hauteur);
	fdf->text[1].data = mlx_get_data_addr(fdf->text[1].image, &fdf->text[1].bpp, &fdf->text[1].size_l, &fdf->text[1].endian);
	fdf->text[2].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text3.xpm", &largeur, &hauteur);
	fdf->text[2].data = mlx_get_data_addr(fdf->text[2].image, &fdf->text[2].bpp, &fdf->text[2].size_l, &fdf->text[2].endian);
	fdf->text[3].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text2.xpm", &largeur, &hauteur);
	fdf->text[3].data = mlx_get_data_addr(fdf->text[3].image, &fdf->text[3].bpp, &fdf->text[3].size_l, &fdf->text[3].endian);
	fdf->text[4].image = mlx_xpm_file_to_image(fdf->mlx_ptr, "./text4.xpm", &largeur, &hauteur);
	fdf->text[4].data = mlx_get_data_addr(fdf->text[4].image, &fdf->text[4].bpp, &fdf->text[4].size_l, &fdf->text[4].endian);
	(void)fdf;
	return (0);
}

/*t_fdf	ft_cub_init(char *av)
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(t_fdf));
	fdf.data = get_data(av);
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, screenWidth, screenHeight, "Cub3D");
	fdf.text[0].image = mlx_new_image(fdf.mlx_ptr, screenWidth, screenHeight);
	fdf.text[0].data = mlx_get_data_addr(fdf.text[0].image, &fdf.text[0].bpp, &fdf.text[0].size_l, &fdf.text[0].endian);
	int largeur = 1920;
	int hauteur = 1080;
	fdf.text[1].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "./text1.xpm", &largeur, &hauteur);
	fdf.text[1].data = mlx_get_data_addr(fdf.text[1].image, &fdf.text[1].bpp, &fdf.text[1].size_l, &fdf.text[1].endian);
	fdf.text[2].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "./text3.xpm", &largeur, &hauteur);
	fdf.text[2].data = mlx_get_data_addr(fdf.text[2].image, &fdf.text[2].bpp, &fdf.text[2].size_l, &fdf.text[2].endian);
	fdf.text[3].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "./text2.xpm", &largeur, &hauteur);
	fdf.text[3].data = mlx_get_data_addr(fdf.text[3].image, &fdf.text[3].bpp, &fdf.text[3].size_l, &fdf.text[3].endian);
	fdf.text[4].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "./text4.xpm", &largeur, &hauteur);
	fdf.text[4].data = mlx_get_data_addr(fdf.text[4].image, &fdf.text[4].bpp, &fdf.text[4].size_l, &fdf.text[4].endian);
	//fdf.floor = get_floor(fdf.data.f);
	fdf.texture = get_texture(fdf);
	fdf.movespeed = 0.0001;
	fdf.rotspeed = 0.0001; //0.033 * 1.8;
	fdf.posX = 22.0, fdf.posY = 11.5;  //x and y start position
	if (!ft_strcmp(fdf.data.dir_player, "N"))
		fdf.dirX = -1;
	else if (!ft_strcmp(fdf.data.dir_player, "S"))
		fdf.dirX = 1;
	else
		fdf.dirX = 0;
	if (!ft_strcmp(fdf.data.dir_player, "W"))
		fdf.dirY = -1;
	else if (!ft_strcmp(fdf.data.dir_player, "E"))
		fdf.dirY = 1;
	else
		fdf.dirY = 0; //initial direction vector
	// fdf.planeX = 0, fdf.planeY = 0.66; //the 2d raycaster version of camera plane
	if (!ft_strcmp(fdf.data.dir_player, "N"))
		fdf.planeY = 0.66;
	else if (!ft_strcmp(fdf.data.dir_player, "S"))
		fdf.planeY = -0.66;
	else
		fdf.planeY = 0;
	if (!ft_strcmp(fdf.data.dir_player, "E"))
		fdf.planeX = 0.66;
	else if (!ft_strcmp(fdf.data.dir_player, "W"))
		fdf.planeX = -0.66;
	else
		fdf.planeX = 0;
	if (!ft_strcmp(fdf.data.dir_player, "N"))
		fdf.planeY = 0.66;
	else if (!ft_strcmp(fdf.data.dir_player, "S"))
		fdf.planeY = -0.66;
	else
		fdf.planeY = 0;
	// init_controls(&fdf);
    return (fdf);
}*/

// fdf.text[1].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "data.no", &largeur, &hauteur);
// fdf.text[2].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "data.ea", &largeur, &hauteur);
// fdf.text[3].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "data.we", &largeur, &hauteur);
// fdf.text[4].image = mlx_xpm_file_to_image(fdf.mlx_ptr, "data.so", &largeur, &hauteur);
// fdf.posX = fdf.data.x, fdf.posY = fdf.data.y;

/*if (fdf.data.dir_player == NO)
	fdf.planeY = 0.66;
else if (fdf.data.dir_player == SO)
	fdf.planeY = -0.66;
else
	fdf.planeY = 0;

if (fdf.data.dir_player == EA)
	fdf.planeX = 0.66;
else if (fdf.data.dir_player == WE)
	fdf.planeX = -0.66;
else
	fdf.planeX = 0;

if (fdf.data.dir_player == NO)
	fdf.planeY = 0.66;
else if (fdf.data.dir_player == SO)
	fdf.planeY = -0.66;
else
	fdf.planeY = -0.66;*/

/*if (fdf.data.dir_player == NO)
	fdf.dirX = -1;
else if (fdf.data.dir_player == SO)
	fdf.dirX = 1;
else
	fdf.dirX = 0;

if (fdf.data.dir_player == WE)
	fdf.dirY = -1;
else if (fdf.data.dir_player == EA)
	fdf.dirY = 1;
else
	fdf.dirY = 0;*/
