/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/01 13:58:35 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_map(t_cub3d *s)
{
	if (read_map(s))
		return (EXIT_FAILURE);
	if (check_walls(s))
		return (EXIT_FAILURE);
}

bool	check_walls(t_cub3d *s)
{
	int	y;
	int	x;

	y = 8;
	while (s->map[y])
	{
		s->mapX = ft_strlen(s->map[y]);
		if (y == 8 || y == s->mapY)
		{
			x = 0;
			while (x < s->mapX)
			{
				if (s->map[y][x] == '1' || s->map[y][x] == ' ')
					x++;
				else
					return (EXIT_FAILURE);
			}
			y++;
		}
		else if (y > 8 && y < s->mapY && chk_mid_map(s->mapX, y, s->map) == 0)
			y++;
	}
	return (EXIT_SUCCESS);
}

bool	chk_mid_map(int mapX, int y, char **map)
{
	int		x;
	bool	start;
	bool	end;

	start = false;
	end = false;
	while (map[y][x])
	{
		if (map[y][x] == '1' && map[y - 1][x] == '1' && start == false)
			start = true;
		else if (x == mapX && map[y][x] == '1' && map[y - 1][x] == '1')
			end = true;
		x++;
	}
	if (start == true && end == true)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

bool	read_map(t_cub3d *s)
{
	int32_t		size_read;
	static char	*buff;

	size_read = -1;
	buff = ft_calloc(10000, sizeof(char));
	while (size_read != 0)
		size_read = read(s->fd, buff, 10000);
	s->map = ft_split(buff, '\n');
	s->mapY = ft_linecount(buff, '\n');
	if (!s->map || !buff || size_read == -1)
		return (EXIT_FAILURE);
	if (check_invalid_char(s))
	{
		error_msg("The map contain invalid characters.");
		return (EXIT_FAILURE);
	}
	free(buff);
	close(s->fd);
	return (EXIT_SUCCESS);
}

bool	check_invalid_char(t_cub3d *s)
{
	int		i;
	int		j;
	bool	pos_ini;

	i = 8;
	pos_ini = false;
	while (s->map[i])
	{
		j = 0;
		while (s->map[i][j])
		{
			if (s->map[i][j] != '0' || s->map[i][j] != '1')
			{
				if ((s->map[i][j] == 'N' || s->map[i][j] == 'S'
						|| s->map[i][j] == 'E' || s->map[i][j] == 'W')
					&& pos_ini == false)
					pos_ini = true;
				else
					return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
bool	check_extension(char *av)
{
	while (*av)
	{
		if (*av == '.')
		{
			if (!ft_strncmp(av, ".cub\0", 5))
				return (EXIT_SUCCESS);
		}
		av++;
	}
	return (EXIT_FAILURE);
}

int	main(int ac, char *av[])
{
	t_cub3d shlk; //init t_cub3d.
	if (ac == 2)
	{
		shlk.fd = open(&av[1], O_RDONLY); //av[1] is the file patch.
		if (shlk.fd == -1)                //if -1 error.
			error_msg("The file couldn't be read, check the map.");
		if (check_extension(av[1]))
			error_msg("Check the map extension.");
		if (check_map(&shlk))
		{
			free_map(shlk.map);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
