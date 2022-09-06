/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:57:08 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/06 17:29:08 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

# define screenWidth 640
# define screenHeight 480
# define mapWidth 24
# define mapHeight 24

typedef enum s_elements
{
	NO,
	SO,
	WE,
	EA,
	IMG_COUNT,
}				t_elements;

typedef enum s_rgb
{
	R,
	G,
	B,
	RGB,
}				t_rgb;

typedef struct s_mlx
{
	mlx_t		*mlx_cub;
	void		*window;
	void		*context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}				t_mlx_cub;

typedef struct s_raycast
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		time;
	double		oldtime;
}				t_raycast;

typedef struct s_cub3d
{
	char		**map;
	int32_t		mapy;
	int32_t		mapx;
	xpm_t		*wall[IMG_COUNT];
	int			c_rgb[RGB];
	int			f_rgb[RGB];
	t_raycast	rayc;
	t_mlx_cub	mlx;
}				t_cub3d;

/* Map Checker */

bool			chk_mid_map(int mapX, int y, char **map);
bool			check_walls(t_cub3d *s);
bool			check_invalid_char(t_cub3d *s);
bool			check_extension(char *av);
bool			check_map(t_cub3d *s);

/* Map Elements */

bool			read_map(t_cub3d *s, char *av);
bool			process_elements(char **map, t_cub3d *s);
void			create_texture(char *map, xpm_t **wall);
bool			create_color(t_cub3d *s, int y);
bool			check_elements(t_cub3d *s);

/* Utils */

int				ft_linecount(const char *str, char c);
void			free_map(char **map);
void			error_msg(char *error);

/* Utils Map */

bool			chk_predecessor_line(int y, char **map);
int				map_start(char **map);

#endif