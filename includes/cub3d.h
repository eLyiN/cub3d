/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:57:08 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/01 19:13:24 by aarribas         ###   ########.fr       */
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

typedef struct cub3d
{
	int		fd;
	char	**map;
	int32_t	mapY;
	int32_t	mapX;

}			t_cub3d;

/* Map Checker */
bool		read_map(t_cub3d *s);
bool		chk_mid_map(int mapX, int y, char **map);
bool		check_walls(t_cub3d *s);
bool		check_invalid_char(t_cub3d *s);
bool		check_extension(char *av);
bool		check_map(t_cub3d *s);
bool		chk_predecessor_line(int y, char **map);

/* Utils */

int			ft_linecount(const char *str, char c);
void		free_map(char **map);
void		error_msg(char *error);

#endif