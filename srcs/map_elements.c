/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:27:36 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/06 17:27:57 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	read_map(t_cub3d *s, char *av)
{
	int32_t		size_read;
	static char	*buff;
	int			fd;

	fd = open(av, O_RDONLY);
	size_read = -1;
	buff = ft_calloc(10000, sizeof(char));
	while (size_read != 0)
		size_read = read(fd, buff, 10000);
	s->map = ft_split(buff, '\n');
	s->mapy = ft_linecount(buff, '\n');
	if (!s->map || !buff || size_read == -1)
		return (EXIT_FAILURE);
	free(buff);
	close(fd);
	return (EXIT_SUCCESS);
}

bool	check_elements(t_cub3d *s)
{
	int	y;
	int	elements;

	y = 0;
	elements = 0;
	while (y < s->mapy)
	{
		printf("%s\n", s->map[y]);
		if (!ft_strncmp("NO", s->map[y], 2) || !ft_strncmp("SO", s->map[y], 2)
			|| !ft_strncmp("WE", s->map[y], 2) || !ft_strncmp("EA", s->map[y],
				2) || !ft_strncmp("F ", s->map[y], 2) || !ft_strncmp("C ",
				s->map[y], 2))
			elements += 1;
		y++;
		printf("elements:%d\n", elements);
	}
	if (elements == 6)
		process_elements(s->map, s);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	process_elements(char **map, t_cub3d *s)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (!ft_strncmp("NO", map[y], 2) || !ft_strncmp("SO", map[y], 2)
			|| !ft_strncmp("WE", map[y], 2) || !ft_strncmp("EA", map[y], 2))
			create_texture(map[y], s->wall);
		else if (!ft_strncmp("F ", map[y], 2) || !ft_strncmp("C ", map[y], 2))
			if (create_color(s, y))
				return (EXIT_FAILURE);
		y++;
	}
	return (EXIT_SUCCESS);
}

bool	create_color(t_cub3d *s, int y)
{
	int		x;
	char	**rgb;

	x = 0;
	while (!ft_isdigit(s->map[y][x]))
		x++;
	rgb = ft_split(s->map[y] + x, ',');
	if (!rgb[1] || !rgb[2])
		return (EXIT_FAILURE);
	if (!ft_strncmp("C ", s->map[y], 2))
	{
		if (ft_atoi(rgb[0]) > 0 && ft_atoi(rgb[0]) <= 255)
			s->c_rgb[0] = ft_atoi(rgb[0]);
		if (ft_atoi(rgb[1]) > 0 && ft_atoi(rgb[1]) <= 255)
			s->c_rgb[1] = ft_atoi(rgb[1]);
		if (ft_atoi(rgb[2]) >= 0 && ft_atoi(rgb[2]) <= 255)
			s->c_rgb[2] = ft_atoi(rgb[2]);
	}
	if (!ft_strncmp("F ", s->map[y], 2))
	{
		if (ft_atoi(rgb[0]) > 0 && ft_atoi(rgb[0]) <= 255)
			s->f_rgb[0] = ft_atoi(rgb[0]);
		if (ft_atoi(rgb[1]) > 0 && ft_atoi(rgb[1]) <= 255)
			s->f_rgb[1] = ft_atoi(rgb[1]);
		if (ft_atoi(rgb[2]) >= 0 && ft_atoi(rgb[2]) <= 255)
			s->f_rgb[2] = ft_atoi(rgb[2]);
	}
	return (EXIT_SUCCESS);
}

void	create_texture(char *map, xpm_t **wall)
{
	int	i;

	if (!ft_strncmp("NO", map, 2))
		i = 0;
	else if (!ft_strncmp("SO", map, 2))
		i = 1;
	else if (!ft_strncmp("WE", map, 2))
		i = 2;
	else if (!ft_strncmp("EA", map, 2))
		i = 3;
	wall[i] = mlx_load_xpm42(ft_strchr(map, '.'));
	printf("string:%s\n", ft_strchr(map, '.'));
	printf("i :%d\n", i);
	if (!wall[i])
		error_msg("Path or file XPM may be corrupt.");
}
