/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 17:24:20 by aarribas         ###   ########.fr       */
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
	load_images(s);
	mlx_loop_hook(s->mlx.mlx_cub, background_hook, s);
	mlx_loop_hook(s->mlx.mlx_cub, raycasting, s);
	mlx_loop_hook(s->mlx.mlx_cub, wasd_hook, s);
	mlx_loop_hook(s->mlx.mlx_cub, left_right_cam, s);
	mlx_loop(s->mlx.mlx_cub);
	mlx_terminate(s->mlx.mlx_cub);
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
		check_walls(&shlk);
		check_pos_ini(&shlk);
		check_invalid_char(&shlk);
		init_game(&shlk);
	}
	else
		error_msg("Too many arguments, please try again.");
	return (EXIT_SUCCESS);
}
