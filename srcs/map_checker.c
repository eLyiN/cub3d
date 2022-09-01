/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:28:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/01 19:22:49 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * chk_mid_map() Will check if the first character of the line has another wall
 * upside, and will to the same for the last character of the line.
 * otherwise the false status will not change. 
*/

bool	chk_mid_map(int mapX, int y, char **map)
{
	int		x;
	bool	start;
	bool	end;

	start = false;
	end = false;
	x = 0;
	while (map[y][x])
	{
		if (map[y][x] == '1' && map[y - 1][x] == '1' && start == false)
			start = true;
		if (x == (mapX - 1) && map[y][x] == '1' && map[y - 1][x] == '1'
			&& end == false)
			end = true;
		if (map[y - 1][mapX] == '\0' && chk_predecessor_line((y - 1), map) == 0)
			end = true;
		x++;
	}
	if (start == true && end == true)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

/**
 * chk_predecessor_line() is created to check if the currently line 
 * that is being checked is longer than the predecessor line. For that
 * I encountered that the problem could be solved adding a function to check
 * if the predecessor line is fully closed with the next one. 
 * This is very interesting and I think it should be documented.
 */

bool	chk_predecessor_line(int y, char **map)
{
	int	size;

	size = ft_strlen(map[y]);
	if (map[y + 1][size - 1] == '1')
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

bool	check_walls(t_cub3d *s)
{
	int	y;
	int	x;

	y = 6;
	while (s->map[y])
	{
		printf("WHILE: %s\n", s->map[y]);
		s->mapX = ft_strlen(s->map[y]);
		if (y == 6 || y == (s->mapY - 1))
		{
			x = 0;
			while (x < s->mapX)
			{
				if (s->map[y][x] == '1' || s->map[y][x] == ' ')
					x++;
				else
					return (EXIT_FAILURE);
			}
		}
		else if (y > 6 && y < (s->mapY - 1))
			if (chk_mid_map(s->mapX, y, s->map) == 1)
				return (EXIT_FAILURE);
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
