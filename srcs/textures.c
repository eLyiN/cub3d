/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:33:07 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 16:55:35 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	put_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t	*px;

	px = (uint32_t *)(img->pixels + (img->height * y + x) * sizeof(uint32_t));
	return (*px);
}

mlx_image_t	*decide_texture(t_cub3d *s)
{
	mlx_image_t	*texture;

	if (s->rayc.side == 0 && s->rayc.raydirx > 0)
		texture = s->wall[SO];
	if (s->rayc.side == 0 && s->rayc.raydirx <= 0)
		texture = s->wall[NO];
	if (s->rayc.side == 1 && s->rayc.raydiry > 0)
		texture = s->wall[EA];
	if (s->rayc.side == 1 && s->rayc.raydiry <= 0)
		texture = s->wall[WE];
	return (texture);
}

void	texturing_calculations(t_cub3d *s, int x)
{
	mlx_image_t	*tex;

	if (s->rayc.side == 0)
		s->texturing.wallx = s->rayc.posy + s->rayc.perpwalldist
			* s->rayc.raydiry;
	else
		s->texturing.wallx = s->rayc.posx + s->rayc.perpwalldist
			* s->rayc.raydirx;
	s->texturing.wallx -= floor((s->texturing.wallx));
	tex = decide_texture(s);
	s->texturing.texx = (int)(s->texturing.wallx * (double)tex->width);
	s->texturing.texx = tex->width - s->texturing.texx - 1;
	s->texturing.step = 1.0 * tex->height / s->rayc.lineheight;
	s->texturing.texpos = (s->texturing.drawstart - s->mlx.height / 2
			+ s->rayc.lineheight / 2) * s->texturing.step;
	draw_textures(s, tex, x);
}
