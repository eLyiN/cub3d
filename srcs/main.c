/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/06 14:39:01 by aarribas         ###   ########.fr       */
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

bool	check_elements(t_cub3d *s)
{
	int	y;
	int	elements;

	y = 0;
	elements = 0;
	while (y < s->mapY)
	{
		printf("%s\n", s->map[y]);
		if (!ft_strncmp("NO", s->map[y], 2) || !ft_strncmp("SO", s->map[y], 2)
			|| !ft_strncmp("WE", s->map[y], 2) || !ft_strncmp("EA", s->map[y],
				2) || !ft_strncmp("F ", s->map[y], 2) || !ft_strncmp("C ",
				s->map[y], 2))
			elements += 1;
		y++;
		printf("elements:%d\n", elements);
	}
	if (elements == 6)
		process_elements(s->map, s);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	process_elements(char **map, t_cub3d *s)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (!ft_strncmp("NO", map[y], 2) || !ft_strncmp("SO", map[y], 2)
			|| !ft_strncmp("WE", map[y], 2) || !ft_strncmp("EA", map[y], 2))
			create_texture(map[y], s->wall);
		/*else if (!ft_strncmp("F ", map[y], 2) || !ft_strncmp("C ", map[y], 2))
			create_color(map[y]);*/
		y++;
	}
}

void	create_texture(char *map, xpm_t **wall)
{
	int	i;

	if (!ft_strncmp("NO", map, 2))
		i = 0;
	else if (!ft_strncmp("SO", map, 2))
		i = 1;
	else if (!ft_strncmp("WE", map, 2))
		i = 2;
	else if (!ft_strncmp("EA", map, 2))
		i = 3;
	wall[i] = mlx_load_xpm42(ft_strchr(map, '.'));
	printf("string:%s\n", ft_strchr(map, '.'));
	printf("i :%d\n", i);
	if (!wall[i])
		error_msg("Path or file XPM may be corrupt.");
}

void	init_game(t_mlx_cub *mlx)
{
	mlx->mlx_cub = mlx_init(mlx->width, mlx->height, "cub3d", true);
	mlx_loop(mlx->mlx_cub);
	mlx_terminate(mlx->mlx_cub);
}

void	init_config(t_raycast *ray, t_mlx_cub *mlx)
{
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->time = 0;
	ray->oldTime = 0;
	mlx->height = screenHeight;
	mlx->width = screenWidth;
}

int	main(int ac, char *av[])
{
	t_cub3d	shlk;

	if (ac == 2)
	{
		shlk.fd = open(av[1], O_RDONLY);
		if (shlk.fd == -1)
			error_msg("The file couldn't be read, check the map.");
		if (check_extension(av[1]))
			error_msg("Check the map extension.");
		if (check_map(&shlk))
		{
			free_map(shlk.map);
			error_msg("Map is not fully closed or have multiples init pos.");
		}
		if (check_elements(&shlk))
			error_msg("Something goes wrong with the elements in the map.");
		init_config(&shlk.rayc, &shlk.mlx);
		init_game(&shlk.mlx);
	}
	return (EXIT_SUCCESS);
}
