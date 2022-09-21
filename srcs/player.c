/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:06:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/21 23:36:27 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	wasd_hook(void *param)
{
	t_cub3d	*s;

	s = param;
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_W))
	{
		s->rayc.posx += (s->rayc.dirx * MOV_SP);
		s->rayc.posy += (s->rayc.diry * MOV_SP);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_S))
	{
		s->rayc.posx -= (s->rayc.dirx * MOV_SP);
		s->rayc.posy -= (s->rayc.diry * MOV_SP);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_D))
	{
		s->rayc.posx += (s->rayc.planex * MOV_SP);
		s->rayc.posy += (s->rayc.planey * MOV_SP);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_A))
	{
		s->rayc.posx -= (s->rayc.planex * MOV_SP);
		s->rayc.posy -= (s->rayc.planey * MOV_SP);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_P))
	{
		printf("sidedistx: %f\n", s->rayc.sidedistx);
		printf("sidedisty: %f\n", s->rayc.sidedisty);
		printf("deltadistx: %f\n", s->rayc.deltadistx);
		printf("deltadisty: %f\n", s->rayc.deltadisty);
		printf("stepx: %d\n", s->rayc.stepx);
		printf("stepy: %d\n", s->rayc.stepy);
		printf("mapx: %d\n", s->rayc.mapx);
		printf("mapy: %d\n", s->rayc.mapy);
		printf("playerX: %f\n", s->rayc.posx);
		printf("playerY: %f\n", s->rayc.posy);
	}
}

void	left_right_cam(void *param)
{
	t_cub3d	*s;
	double	olddirx;
	double	oldplanex;

	s = param;
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_LEFT))
	{
		olddirx = s->rayc.dirx;
		s->rayc.dirx = s->rayc.dirx * cos(-RT_SP) - s->rayc.diry * sin(-RT_SP);
		s->rayc.diry = olddirx * sin(-RT_SP) + s->rayc.diry * cos(-RT_SP);
		oldplanex = s->rayc.planex;
		s->rayc.planex = s->rayc.planex * cos(-RT_SP) - s->rayc.planey
			* sin(-RT_SP);
		s->rayc.planey = oldplanex * sin(-RT_SP) + s->rayc.planey * cos(-RT_SP);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_RIGHT))
	{
		olddirx = s->rayc.dirx;
		s->rayc.dirx = s->rayc.dirx * cos(RT_SP) - s->rayc.diry * sin(RT_SP);
		s->rayc.diry = olddirx * sin(RT_SP) + s->rayc.diry * cos(RT_SP);
		oldplanex = s->rayc.planex;
		s->rayc.planex = s->rayc.planex * cos(RT_SP) - s->rayc.planey
			* sin(RT_SP);
		s->rayc.planey = oldplanex * sin(RT_SP) + s->rayc.planey * cos(RT_SP);
	}
}
