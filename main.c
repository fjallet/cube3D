#include "fdf.h"

void	ft_draw3D(t_fdf *f, long long **texture)
{
	// long long **texture = get_texture(f);
	ft_draw_ceillings_floors(f);
	for (int x = 0; x < screenWidth; x++)
		{
			ft_forward_back(f);
			ft_left_right(f);
			ft_rotate_right_left(f);
			ray_screen(f, x);
			f->mapX = (int)f->posX; // current square the ray is in;
     		f->mapY = (int)f->posY; // current square the ray is in;
			ray_delta_step(f);
			//was there a wall hit?
      		//f->side; was a NS or a EW wall hit?
			first_step_direction(f);
			f->hit = 0;
			check_wall_hit(f);
			ray_size(f);
			wall_size(f);
			//texturing calculations
      		choose_text(f);
			ft_draw_walls(f, x, texture);
		}
		//draw_raycasting(f, buffer);
}

/*void	draw_pixel4(t_fdf *fdf, int x1, int y1, int color)
{
	size_t	index;
	if (y1 >= screenHeight || x1 >= screenWidth || x1 < 0 || y1 < 0)
		return ;
	index = (y1 * fdf->text[0].size_l) + x1 * (fdf->text[0].bpp / 8);
	fdf->text[0].data[index + 3] = (color & 0xFF000000) >> 24;
	fdf->text[0].data[index + 2] = (color & 0x00FF0000) >> 16;
	fdf->text[0].data[index + 1] = (color & 0x0000FF00) >> 8;
	fdf->text[0].data[index] = color & 0x000000FF;
}*/

int	expose_hook(t_fdf *f)
{
	// int test = 9696163;
	ft_draw3D(f, f->texture);
	// draw_pixel4(f, 5, 6, test);
	// draw_pixel4(f, 5, 7, test);
	// draw_pixel4(f, 5, 8, test);
	// draw_pixel4(f, 5, 9, test);
	// draw_pixel4(f, 5, 10, test);
	// draw_pixel4(f, 5, 11, test);
	// draw_pixel4(f, 5, 12, test);
	// draw_pixel4(f, 5, 13, test);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->text[0].image, 0, 0);
	return (0);
}

void	print_arg(t_arg *data)
{
	printf("no == %s\n", data->no);
	printf("so == %s\n", data->so);
	printf("we == %s\n", data->we);
	printf("ea == %s\n", data->ea);
	printf("f == %s\nc == %s\n", data->f, data->c);
	printf("dir_player == %c\n", data->dir_player);
	printf("pos = [%d][%d]\n", data->y, data->x);
	printf("largeur : %i\n", data->longest_line);
	printf("longeur : %i\n", data->size_map);
	int i = -1;
	int j;
	printf("\n");
	while (data->map[++i])
	{
		j = -1;
		while(data->map[i][++j])
			printf("%c", data->map[i][j]);
		printf("\n");
	}
	printf("\n");
	i = 0;
	while (i < data->size_map)
	{
		j = 0;
		while(j < data->longest_line)
		{
			printf("%i", data->tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2 || check_file(av[1]))
	{
		printf("wrong filename\n");
		return (0);
	}
	ft_bzero(&fdf, sizeof(fdf));
	ft_bzero(&fdf.data, sizeof(t_arg));
	if (cube3D_init(&fdf, av[1]))
		return (1);
	print_arg(&fdf.data);
	printf("colors :\nf = %i et c = %i\n", fdf.floor, fdf.ceiling);
	if (img_init(&fdf))
		return (1);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_press, &fdf);
	mlx_loop_hook(fdf.mlx_ptr, expose_hook, &fdf);
	mlx_hook(fdf.win_ptr, 3, 1L << 1, key_release, &fdf);
	mlx_loop(fdf.mlx_ptr);
	(void)fdf;
	return (0);
}