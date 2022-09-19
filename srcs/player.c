/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:06:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/19 18:45:03 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	wasd_hook(void *param)
{
	t_cub3d	*s;

	s = param;
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_W))
	{
		s->rayc.posx += (s->rayc.dirx * MOVE_SPEED) + (s->rayc.planex
				* MOVE_SPEED);
		s->rayc.posy += (s->rayc.diry * MOVE_SPEED) + (s->rayc.planey
				* MOVE_SPEED);
	}
	else if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_S))
	{
		s->rayc.posx -= (s->rayc.dirx * MOVE_SPEED) + (s->rayc.planex
				* MOVE_SPEED);
		s->rayc.posy -= (s->rayc.diry * MOVE_SPEED) + (s->rayc.planey
				* MOVE_SPEED);
	}
	else if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_D))
	{
		s->rayc.posx += (s->rayc.planex * MOVE_SPEED);
		s->rayc.posy += (s->rayc.planey * MOVE_SPEED);
	}
	else if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_A))
	{
		s->rayc.posx -= (s->rayc.planex * MOVE_SPEED);
		s->rayc.posy -= (s->rayc.planey * MOVE_SPEED);
	}
}

void	left_right_cam(void *param)
{
	t_cub3d *s;
	double olddirx;
	double oldplanex;

	s = param;
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_LEFT))
	{
		olddirx = s->rayc.dirx;
		s->rayc.dirx = s->rayc.dirx * cos(-ROT_SPEED) - s->rayc.diry
			* sin(-ROT_SPEED);
		s->rayc.diry = olddirx * sin(-ROT_SPEED) + s->rayc.diry
			* cos(-ROT_SPEED);
		oldplanex = s->rayc.planex;
		s->rayc.planex = s->rayc.planex * cos(-ROT_SPEED) - s->rayc.planey
			* sin(-ROT_SPEED);
		s->rayc.planey = oldplanex * sin(-ROT_SPEED) + s->rayc.planey
			* cos(-ROT_SPEED);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_RIGHT))
	{
		olddirx = s->rayc.dirx;
		s->rayc.dirx = s->rayc.dirx * cos(ROT_SPEED) - s->rayc.diry
			* sin(ROT_SPEED);
		s->rayc.diry = olddirx * sin(ROT_SPEED) + s->rayc.diry * cos(ROT_SPEED);
		oldplanex = s->rayc.planex;
		s->rayc.planex = s->rayc.planex * cos(ROT_SPEED) - s->rayc.planey
			* sin(ROT_SPEED);
		s->rayc.planey = oldplanex * sin(ROT_SPEED) + s->rayc.planey
			* cos(ROT_SPEED);
	}
}