/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/01 18:21:30 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		free_map(s->map);
		error_msg("The map contain invalid characters.");
		return (EXIT_FAILURE);
	}
	free(buff);
	close(s->fd);
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_cub3d	shlk;

	if (ac == 2)
	{
		shlk.fd = open(av[1], O_RDONLY); //av[1] is the file patch.
		if (shlk.fd == -1)               //if -1 error.
			error_msg("The file couldn't be read, check the map.");
		if (check_extension(av[1]))
			error_msg("Check the map extension.");
		if (check_map(&shlk))
		{
			free_map(shlk.map);
			error_msg("Map is not fully closed or have multiples init pos.");
		}
	}
	return (EXIT_SUCCESS);
}
