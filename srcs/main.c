/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/08/30 00:02:17 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map(t_cub3d *s)
{
	read_map(s);
}

void	read_map(t_cub3d *s)
{
	int32_t		size_read;
	static char	*buff;

	buff = ft_calloc(10000, sizeof(char));
	while (size_read != 0)
	{
		size_read = read(s->fd, buff, 10000);
		if (size_read == -1)
			error_msg("Fail reading the file, check the map.");
	}
	s->map = ft_split(buff, '\n');
	s->mapY = ft_linecount(buff, '\n');
	if (!s->map)
		error_msg("Fail reading the file, check the map.");
	if (check_invalid_char(s))
		error_msg("The map contain invalid characters.");
	free(buff);
}

bool	check_invalid_char(t_cub3d *s)
{
}
bool	check_extension(char *av)
{
	while (*av)
	{
		if (*av == '.')
		{
			if (!ft_strncmp(av, ".cub\0", 5))
				return (EXIT_SUCCESS);
			else
				error_msg("Check the map extension.");
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
		check_extension(av[1]);
		check_map(&shlk); //proceed to check the map.
	}
	return (EXIT_FAILURE);
}