/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:20:32 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/05 22:32:17 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_start(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (ft_strchr(map[y], 'C'))
		{
			while (!ft_strchr(map[y], '1'))
				y++;
			return (y);
		}
		y++;
	}
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
