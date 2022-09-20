/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:28:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 17:28:04 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * chk_mid_map() Will check if the first character of the line has another wall
 * upside, and will to the same for the last character of the line.
 * otherwise the false status will not change. 
*/

void	check_mid_map(int mapX, int y, char **map)
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
		return ;
	else
		error_msg("The map is not closed by walls.");
}

void	check_first_last_line(t_cub3d *s, int y)
{
	int	x;

	x = 0;
	while (x < s->mapx)
	{
		if (s->map[y][x] == '1' || s->map[y][x] == ' ')
			x++;
		else
			error_msg("The map is not closed by walls.");
	}
	return ;
}

void	check_walls(t_cub3d *s)
{
	int	y;
	int	init_y;

	y = map_start(s->map);
	init_y = y;
	while (s->map[y])
	{
		s->mapx = ft_strlen(s->map[y]);
		if (y == init_y || y == (s->mapy - 1))
			check_first_last_line(s, y);
		else if (y > init_y && y < (s->mapy - 1))
			check_mid_map(s->mapx, y, s->map);
		y++;
	}
}

void	check_invalid_char(t_cub3d *s)
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
				error_msg("The map contains invalid characters.");
		}
		y--;
	}
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
