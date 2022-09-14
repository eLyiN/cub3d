/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:28:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/15 00:14:51 by aarribas         ###   ########.fr       */
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

bool	check_walls(t_cub3d *s)
{
	int	y;
	int	x;
	int	init_y;

	y = map_start(s->map);
	init_y = y;
	while (s->map[y])
	{
		s->mapx = ft_strlen(s->map[y]);
		if (y == init_y || y == (s->mapy - 1))
		{
			x = 0;
			while (x < s->mapx)
			{
				if (s->map[y][x] == '1' || s->map[y][x] == ' ')
					x++;
				else
					return (EXIT_FAILURE);
			}
		}
		else if (y > init_y && y < (s->mapy - 1))
			if (chk_mid_map(s->mapx, y, s->map) == 1)
				return (EXIT_FAILURE);
		y++;
	}
	return (EXIT_SUCCESS);
}

bool	check_invalid_char(t_cub3d *s)
{
	int	y;
	int	x;

	y = s->mapy - 1;
	while (ft_strcmp("C ", s->map[y]) > 0)
	{
		x = 0;
		while (s->map[y][x])
		{
			if (ft_strchr("01NESW ", s->map[y][x]))
				x++;
			else
				return (EXIT_FAILURE);
		}
		y--;
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

void	check_map(t_cub3d *s)
{
	if (check_walls(s))
	{
		free_map(s->map);
		error_msg("The map does not contain the necessary elements or is not closed.");
	}
	if (check_pos_ini(s))
	{
		free_map(s->map);
		error_msg("The map contains multiple starting positions.");
	}
	if (check_invalid_char(s))
	{
		free_map(s->map);
		error_msg("The map contains invalid characters.");
	}
}
