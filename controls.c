/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:54:01 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/30 19:23:59 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_fdf *f)
{
	free(f->data.so);
	free(f->data.we);
	free(f->data.ea);
	free(f->data.no);
	free(f->data.f);
	free(f->data.c);
	free_tab(f->data.map);
	free_coord(f->data.tab, f->data.size_map);
	free(f->texture[0]);
	free(f->texture[1]);
	free(f->texture[2]);
	free(f->texture[3]);
	free(f->texture);
	if (f->mlx_ptr && f->text[0].image)
		mlx_destroy_image(f->mlx_ptr, f->text[0].image);
	if (f->mlx_ptr && f->text[1].image)
		mlx_destroy_image(f->mlx_ptr, f->text[1].image);
	if (f->mlx_ptr && f->text[2].image)
		mlx_destroy_image(f->mlx_ptr, f->text[2].image);
	if (f->mlx_ptr && f->text[3].image)
		mlx_destroy_image(f->mlx_ptr, f->text[3].image);
	if (f->mlx_ptr && f->text[4].image)
		mlx_destroy_image(f->mlx_ptr, f->text[4].image);
	if (f->mlx_ptr && f->win_ptr)
		mlx_destroy_window(f->mlx_ptr, f->win_ptr);
	if (f->mlx_ptr)
		mlx_destroy_display(f->mlx_ptr);
	free(f->mlx_ptr);
	exit(0);
}

int	key_press(int keycode, t_fdf *f)
{
	//printf("key_press == %d\n", keycode);
	if (keycode == 65307)
		ft_close(f);
	else if (keycode == 119) // W ou Z
	{
		// printf("f->forward == %d\n", f->forward);
		f->forward = 1;
		// printf("f->forward == %d\n", f->forward);
	}
	else if (keycode == 115) // S ou S
		f->back = 1;
	else if (keycode == 97) // A ou Q
		f->left = 1;
	else if (keycode == 100) // D ou D
		f->right = 1;
	else if (keycode == 65363)
		f->rotate_right = 1;
	else if (keycode == 65361)
		f->rotate_left = 1;
	// else if (keycode == 101)
	// 	zoom(f, 5);
	// expose_hook(f);
	return (0);
}

int	key_release(int keycode, t_fdf *f)
{
	// printf("key_release == %d\n", keycode);
	if (keycode == 65307)
		ft_close(f);
	else if (keycode == 119) // W ou Z
		f->forward = 0;
	else if (keycode == 115) // S ou S
		f->back = 0;
	else if (keycode == 97) // A ou Q
		f->left = 0;
	else if (keycode == 100) // D ou D
		f->right = 0;
	else if (keycode == 65363)
		f->rotate_right = 0;
	else if (keycode == 65361)
		f->rotate_left = 0;
	// else if (keycode == 101)
	// 	zoom(f, 5);
	// expose_hook(f);
	return (0);
}

void	init_controls(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 2, 1L << 0, key_press, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, ft_close, fdf);
	mlx_hook(fdf->win_ptr, 3, 1L << 1, key_release, fdf);// ?
}