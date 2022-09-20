/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:06:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 17:08:01 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	wasd_hook(void *param)
{
	t_cub3d	*s;

	s = param;
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_W))
	{
		s->rayc.posx += (s->rayc.dirx * MOV_SP) + (s->rayc.planex * MOV_SP);
		s->rayc.posy += (s->rayc.diry * MOV_SP) + (s->rayc.planey * MOV_SP);
	}
	else if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_S))
	{
		s->rayc.posx -= (s->rayc.dirx * MOV_SP) + (s->rayc.planex * MOV_SP);
		s->rayc.posy -= (s->rayc.diry * MOV_SP) + (s->rayc.planey * MOV_SP);
	}
	else if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_D))
	{
		s->rayc.posx += (s->rayc.planex * MOV_SP);
		s->rayc.posy += (s->rayc.planey * MOV_SP);
	}
	else if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_A))
	{
		s->rayc.posx -= (s->rayc.planex * MOV_SP);
		s->rayc.posy -= (s->rayc.planey * MOV_SP);
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
