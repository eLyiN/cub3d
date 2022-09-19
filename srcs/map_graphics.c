/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:51:01 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/19 18:58:09 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_images(t_cub3d *s)
{
	s->wall[SO] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[SO]);
	s->wall[NO] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[NO]);
	s->wall[EA] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[EA]);
	s->wall[WE] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[WE]);
	if (!s->wall[SO] || !s->wall[NO] || !s->wall[EA] || !s->wall[WE])
		error_msg("Fail loading texture to image.");
}