/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:45:36 by abouleau          #+#    #+#             */
/*   Updated: 2023/03/18 19:10:14 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <math.h>

# define PI 3.1415926535
# define BUFFER_SIZE 500
# define HAUTEUR 512
# define LARGEUR 1024
# define P2 1.5707963267
# define P3 4.7123889803
# define DR 0.0174533
# define SCREENWIDTH 640 //640//1920
# define SCREENHEIGHT 480 //480//1080

// #define mapWidth 24
// #define mapHeight 24
# define TEXWIDTH 1024
# define TEXHEIGHT 1024

//extern int worldMap[mapWidth][mapHeight];

typedef struct s_data
{
	int		dx;
	int		dy;
	int		slope_director;
	int		slope_error;
	int		x_increment;
	int		y_increment;
}			t_data_slope;

typedef struct s_text
{
	void	*image;
	char	*data;
	int		color;
	int		bpp;
	int		endian;
	int		size_l;
	int		height;
	int		witdh;
}			t_text;

typedef struct s_arg
{
	int		**tab;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		fd;
	char	*str;
	int		get_map;
	char	dir_player;
	int		count_start;
	int		size_map;
	int		longest_line;
	int		x;
	int		y;
	int		error;
	int		error_map;
}			t_arg;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			color;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			mapx;
	int			mapy;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		movespeed;
	double		rotspeed;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	int			texx;
	int			texnum;
	int			texy;
	int			mapwidth;
	int			mapheight;
	long long	**texture;
	t_text		text[5];
	t_arg		data;
	int			floor;
	int			ceiling;
}				t_fdf;

//main.c
void		ft_draw3d(t_fdf *f, long long **texture);
int			expose_hook(t_fdf *f);
int			check_prompt(char **av, int ac);

//ray.c
void		ray_screen(t_fdf *f, int x);
void		ray_delta_step(t_fdf *f);
void		first_step_direction(t_fdf *f);
void		check_wall_hit(t_fdf *f);
void		ray_size(t_fdf *f);

//ray2.c
void		wall_size(t_fdf *f);
void		choose_text(t_fdf *f);
void		ft_draw_walls(t_fdf *f, int x, long long **texture);

// move_player.c
void		ft_rotate_left(t_fdf *f, double olddirx);
void		ft_rotate_right_left(t_fdf *f);
void		ft_left_right(t_fdf *f);
void		ft_forward_back(t_fdf *f);

//	ft_draw.c
void		draw_pixel(t_fdf *fdf, int x1, int y1, int color);
int			get_color( int x, int y, t_text text);
void		ft_draw_ceillings_floors(t_fdf *f);

// control.c
int			ft_close(t_fdf *f);
int			key_press(int keycode, t_fdf *f);
int			key_release(int keycode, t_fdf *f);
void		init_controls(t_fdf *fdf);

// init.c
void		start_pos_init(t_fdf *f, char c);
int			cube3d_init(t_fdf *f, char *av);
int			get_texture(t_fdf *f);
int			img_init(t_fdf *f);

// gnl.c
size_t		ft_strlen1(char *str);
char		*ft_strchr1(char *s, int c);
char		*ft_strjoin1(char *s, char *c);
char		*get_next_line(int fd);

// data.c
char		*check_str(char *str, t_arg *data);
char		**get_map(char *str, char **old_map, t_arg *data);
int			ft_empty_sentence(char *str);
int			get_data(t_arg *data, char *av);
int			get_xpm_img(t_fdf *fdf);

// parsing.c
int			test_map(int i, int j, t_arg *data);
int			map_parsing2(t_arg *data, int i, int j);
int			map_parsing(t_arg *data);
int			create_trgb(int r, int g, int b);
int			get_rgb(char *rgb, int c);

//check.c
int			check_data(t_arg *data);
int			check_argv(char *argv);
int			check_file(char *str, char *suffix);
int			check_rgb(char *rgb);
int			check_line(char *str, t_arg *data);

// cub3D_utils
int			ft_strlen2(char *str);
int			create_int_tab(t_arg *data);
int			get_path(t_arg *data, char **text, char *str);
int			get_shiet(t_arg *data, char **rgb, char *str);
int			ft_ismap(char *str);

//	cub3D_utils2
char		*ft_strdup2(const char *s);

// clean.c
void		free_data(t_arg *data);
void		free_coord(int **map, int count_y);
void		free_tab(char **split);

#endif