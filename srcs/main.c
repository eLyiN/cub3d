/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:47:31 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/06 17:28:06 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_mlx_cub *mlx)
{
	mlx->mlx_cub = mlx_init(mlx->width, mlx->height, "cub3d", true);
	mlx_loop(mlx->mlx_cub);
	mlx_terminate(mlx->mlx_cub);
}

void	init_config(t_raycast *ray, t_mlx_cub *mlx)
{
	ray->dirx = -1;
	ray->diry = 0;
	ray->planex = 0;
	ray->planey = 0.66;
	ray->time = 0;
	ray->oldtime = 0;
	mlx->height = screenHeight;
	mlx->width = screenWidth;
}

int	main(int ac, char *av[])
{
	t_cub3d	shlk;

	if (ac == 2)
	{
		if (read_map(&shlk, av[1]))
		{
			free_map(shlk.map);
			error_msg("The file couldn't be read, check the map.");
		}
		if (check_extension(av[1]))
			error_msg("Check the map extension.");
		if (check_elements(&shlk))
			error_msg("Something goes wrong with the elements in the map.");
		if (check_map(&shlk))
		{
			free_map(shlk.map);
			error_msg("Map is not fully closed or have multiples init pos.");
		}
		init_config(&shlk.rayc, &shlk.mlx);
		init_game(&shlk.mlx);
	}
	return (EXIT_SUCCESS);
}
