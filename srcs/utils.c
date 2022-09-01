/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:11:05 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/01 13:57:54 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_msg(char *error)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
}

int	ft_linecount(const char *str, char c)
{
	int	i;
	int	substr;
	int	in_word;

	i = 0;
	substr = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			in_word = 0;
		}
		else
		{
			if (in_word == 0)
			{
				in_word = 1;
				substr++;
			}
			i++;
		}
	}
	return (substr);
}

void	free_map(char **map)
{
	while (**map)
	{
		free(**map);
		map++;
	}
	free(**map);
}