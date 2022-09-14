/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/15 00:03:16 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_cub3d *s)
{
	s->mlx.height = HEIGHT;
	s->mlx.width = WIDTH;
	s->mlx.mlx_cub = mlx_init(s->mlx.width, s->mlx.height, "cub3d", true);
	s->mlx.window = mlx_new_image(s->mlx.mlx_cub, s->mlx.width, s->mlx.width);
	mlx_image_to_window(s->mlx.mlx_cub, s->mlx.window, 0, 0);
	mlx_loop_hook(s->mlx.mlx_cub, background_hook, s);
	mlx_loop_hook(s->mlx.mlx_cub, raycasting, s);
	mlx_loop_hook(s->mlx.mlx_cub, char_hook, s);
	mlx_loop(s->mlx.mlx_cub);
	mlx_terminate(s->mlx.mlx_cub);
}

void	background_hook(void *param)
{
	t_cub3d	*data;
	int		i;

	data = param;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (i < WIDTH * (HEIGHT / 2))
			mlx_put_pixel(data->mlx.window, i, 0, data->ceiling);
		else if (i > WIDTH * (HEIGHT / 2))
			mlx_put_pixel(data->mlx.window, i, 0, data->floor);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_cub3d	shlk;

	if (ac == 2)
	{
		if (read_map(&shlk, av[1]))
			error_msg("The file couldn't be read, check the map.");
		if (check_extension(av[1]))
			error_msg("Check the map extension.");
		if (check_elements(&shlk))
			error_msg("Something goes wrong with the elements in the map.");
		check_map(&shlk);
		init_game(&shlk);
	}
	return (EXIT_SUCCESS);
}
