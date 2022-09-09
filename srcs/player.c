/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:06:33 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/09 18:02:52 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	char_hook(void *param)
{
	t_cub3d	*s;
	double	olddirx;
	double	oldplanex;

	s = param;
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_W))
	{
		if (s->map[(int)s->rayc.posy][(int)(s->rayc.posx + s->rayc.dirx
				* MOVE_SPEED)] == false)
			s->rayc.posx += s->rayc.dirx * MOVE_SPEED;
		else if (s->map[(int)(s->rayc.posy + s->rayc.diry
					* MOVE_SPEED)][(int)s->rayc.posx] == false)
			s->rayc.posy += s->rayc.diry * MOVE_SPEED;
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_S))
	{
		if (s->map[(int)s->rayc.posy][(int)(s->rayc.posx + s->rayc.dirx
				* MOVE_SPEED)] == false)
			s->rayc.posx -= s->rayc.dirx * MOVE_SPEED;
		else if (s->map[(int)(s->rayc.posy + s->rayc.diry
					* MOVE_SPEED)][(int)s->rayc.posx] == false)
			s->rayc.posy -= s->rayc.diry * MOVE_SPEED;
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_A))
	{
		olddirx = s->rayc.dirx;
		s->rayc.dirx = s->rayc.dirx * cos(-ROT_SPEED) - s->rayc.diry
			* cos(-ROT_SPEED);
		s->rayc.diry = olddirx * sin(-ROT_SPEED) + s->rayc.diry
			* cos(-ROT_SPEED);
		oldplanex = s->rayc.planex;
		s->rayc.planex = s->rayc.planex * cos(-ROT_SPEED) - s->rayc.planey
			* sin(-ROT_SPEED);
		s->rayc.planey = oldplanex * sin(-ROT_SPEED) + s->rayc.planey
			* cos(-ROT_SPEED);
	}
	if (mlx_is_key_down(s->mlx.mlx_cub, MLX_KEY_D))
	{
		olddirx = s->rayc.dirx;
		s->rayc.dirx = s->rayc.dirx * cos(ROT_SPEED) - s->rayc.diry
			* cos(ROT_SPEED);
		s->rayc.diry = olddirx * sin(ROT_SPEED) + s->rayc.diry * cos(ROT_SPEED);
		oldplanex = s->rayc.planex;
		s->rayc.planex = s->rayc.planex * cos(ROT_SPEED) - s->rayc.planey
			* sin(ROT_SPEED);
		s->rayc.planey = oldplanex * sin(ROT_SPEED) + s->rayc.planey
			* cos(ROT_SPEED);
	}
}
