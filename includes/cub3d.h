/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:57:08 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/18 23:17:44 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include "cub3d_macro.h"
# include <fcntl.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

typedef enum s_elements
{
	NO,
	SO,
	WE,
	EA,
	IMG_COUNT,
}					t_elements;

typedef struct s_mlx
{
	mlx_t			*mlx_cub;
	mlx_image_t		*window;
	void			*context;
	int32_t			width;
	int32_t			height;
	double			delta_time;
}					t_mlx_cub;

typedef struct s_texture
{
	double			step;
	double			texpos;
	double			wallx;
	int				texx;
	int				texy;
}					t_texture;

typedef struct s_raycast
{
	double			camerax;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	int				mapx;
	int				mapy;
	double			planex;
	double			planey;
	double			raydirx;
	double			raydiry;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				pixel;
	int				stepx;
	int				stepy;
	int				side;
	int				hit;
	int				lineheight;
}					t_raycast;

typedef struct s_cub3d
{
	char			**map;
	int32_t			mapy;
	int32_t			mapx;
	mlx_texture_t	*png[IMG_COUNT];
	mlx_image_t		*wall[IMG_COUNT];
	uint32_t		ceiling;
	uint32_t		floor;
	t_texture		texturing;
	t_raycast		rayc;
	t_mlx_cub		mlx;
}					t_cub3d;

COLOR				ml_color_at(mlx_image_t *img, int x, int y);
mlx_image_t			*decide_texture(t_cub3d *s);
void				left_right_cam(void *param);

/* Map Checker */

bool				chk_mid_map(int mapX, int y, char **map);
bool				check_walls(t_cub3d *s);
bool				check_invalid_char(t_cub3d *s);
bool				check_extension(char *av);
void				check_map(t_cub3d *s);

/* Map Elements */

bool				read_map(t_cub3d *s, char *av);
void				process_elements(char **map, t_cub3d *s);
void				create_texture(t_cub3d *s, int y);
void				create_color(t_cub3d *s, int y);
bool				check_elements(t_cub3d *s);

/* Initial Position Camera */

bool				check_pos_ini(t_cub3d *s);
bool				set_pos_ini_n(t_raycast *r, int x, int y);
bool				set_pos_ini_e(t_raycast *r, int x, int y);
bool				set_pos_ini_s(t_raycast *r, int x, int y);
bool				set_pos_ini_w(t_raycast *r, int x, int y);

/* Raycasting */

void				raycasting(void *param);
void				draw_walls(t_cub3d *s, int x);
void				perform_dda(t_raycast *r, char **map);
void				raycast_init(t_raycast *r, int x);
void				calculate_step(t_cub3d *s);

/* Utils */

int					ft_linecount(const char *str, char c);
void				free_map(char **map);
void				error_msg(char *error);

/* Color conversion */

uint32_t			get_rgb(int r, int g, int b);
uint32_t			get_rgba(int r, int g, int b, int a);
void				load_color(char **rgb, uint32_t *color);

/* Texturing */

void				texturing_calculations(t_cub3d *s, int drawstart,
						int drawend, int x);
void				texture_step(t_cub3d *s, int drawstart, int drawend,
						int texx, int x);

/* Utils Map */

bool				chk_predecessor_line(int y, char **map);
int					map_start(char **map);

void				background_hook(void *param);
void				draw_verline(mlx_image_t *screen, int y1, int y2, int x,
						int32_t color_test);

void				wasd_hook(void *param);

#endif