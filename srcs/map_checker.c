/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:28:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/01 17:56:23 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

bool	check_invalid_char(t_cub3d *s)
{
	int		i;
	int		j;
	bool	pos_ini;

	i = 6;
	while (s->map[i])
	{
		printf("MAP: %s\n", s->map[i]);
		i++;
	}
	i = 6;
	pos_ini = false;
	while (s->map[i])
	{
		j = 0;
		while (s->map[i][j])
		{
			if (s->map[i][j] != '0' || s->map[i][j] != '1'
				|| s->map[i][j] != ' ')
			{
				if ((s->map[i][j] == 'N' || s->map[i][j] == 'S'
						|| s->map[i][j] == 'E' || s->map[i][j] == 'W')
					&& pos_ini == false)
					pos_ini = true;
				else if ((s->map[i][j] == 'N' || s->map[i][j] == 'S'
							|| s->map[i][j] == 'E' || s->map[i][j] == 'W')
						&& pos_ini == true)
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

bool	check_map(t_cub3d *s)
{
	if (read_map(s))
		return (EXIT_FAILURE);
	if (check_walls(s))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
