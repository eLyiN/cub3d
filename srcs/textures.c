/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:33:07 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/15 23:46:07 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	texturing_calculations(t_cub3d *s, int drawstart, int drawend, int x)
{
	double	wallx;
	int		texx;

	if (s->rayc.side == 0)
		wallx = s->rayc.posy + s->rayc.perpwalldist * s->rayc.raydiry;
	else
		wallx = s->rayc.posx + s->rayc.perpwalldist * s->rayc.raydirx;
	wallx -= floor((wallx));
	texx = (int)(wallx * (double)TEXW);
	if (s->rayc.side == 0 && s->rayc.raydirx > 0)
		texx = TEXW - texx - 1;
	if (s->rayc.side == 1 && s->rayc.raydiry < 0)
		texx = TEXW - texx - 1;
	texture_step(s, drawstart, drawend, texx, x);
}

void	texture_step(t_cub3d *s, int drawstart, int drawend, int texx, int x)
{
	double	step;
	double	texpos;
	int		y;
	int		texy;
	COLOR	c;

	step = 1.0 * TEXH / s->rayc.lineheight;
	texpos = (drawstart - HEIGHT / 2 + s->rayc.lineheight / 2) * step;
	y = drawstart;
	while (y < drawend)
	{
		texy = (int)texpos & (TEXH - 1);
		texpos += step;
		c = ml_color_at(s->wall[0], texx, texy);
		mlx_put_pixel(s->mlx.window, x, y, c);
		y++;
	}
}

COLOR	ml_color_at(mlx_texture_t *img, int x, int y)
{
	COLOR *pixel;

	pixel = (COLOR *)(img->pixels + (x + y * img->height) * sizeof(COLOR));
	return (*pixel);
}