/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:27:36 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 16:18:56 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	read_map(t_cub3d *s, char *av)
{
	int32_t		size_read;
	static char	*buff;
	int			fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		error_msg("The file may not exist.");
	size_read = -1;
	buff = ft_calloc(10000, sizeof(char));
	while (size_read != 0)
		size_read = read(fd, buff, 10000);
	s->map = ft_split(buff, '\n');
	s->mapy = ft_linecount(buff, '\n');
	if (!s->map || !buff || size_read == -1)
	{
		free(buff);
		close(fd);
		free_map(s->map);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	create_texture(t_cub3d *s, int y)
{
	int	i;

	if (!ft_strncmp("NO", s->map[y], 2))
		i = 0;
	else if (!ft_strncmp("SO", s->map[y], 2))
		i = 1;
	else if (!ft_strncmp("WE", s->map[y], 2))
		i = 2;
	else if (!ft_strncmp("EA", s->map[y], 2))
		i = 3;
	s->png[i] = mlx_load_png(ft_strchr(s->map[y], '.'));
	if (!s->png[i])
	{
		free_map(s->map);
		error_msg("Path or file PNG may be corrupt.");
	}
}

void	process_elements(char **map, t_cub3d *s)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (!ft_strncmp("NO", map[y], 2) || !ft_strncmp("SO", map[y], 2)
			|| !ft_strncmp("WE", map[y], 2) || !ft_strncmp("EA", map[y], 2))
			create_texture(s, y);
		else if (!ft_strncmp("F ", map[y], 2) || !ft_strncmp("C ", map[y], 2))
			create_color(s, y);
		y++;
	}
}

bool	check_elements(t_cub3d *s)
{
	int	y;
	int	elements;

	y = 0;
	elements = 0;
	while (y < s->mapy)
	{
		if (!ft_strncmp("NO", s->map[y], 2) || !ft_strncmp("SO", s->map[y], 2)
			|| !ft_strncmp("WE", s->map[y], 2) || !ft_strncmp("EA", s->map[y],
				2) || !ft_strncmp("F ", s->map[y], 2) || !ft_strncmp("C ",
				s->map[y], 2))
			elements += 1;
		y++;
	}
	if (elements != 6)
		error_msg("Missing elements in the map.");
	process_elements(s->map, s);
	return (EXIT_SUCCESS);
}
