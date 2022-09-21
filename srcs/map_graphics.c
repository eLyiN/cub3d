/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:51:01 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/21 23:37:53 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_images(t_cub3d *s)
{
	s->wall[SO] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[SO]);
	mlx_delete_texture(s->png[SO]);
	s->wall[NO] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[NO]);
	mlx_delete_texture(s->png[NO]);
	s->wall[EA] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[EA]);
	mlx_delete_texture(s->png[EA]);
	s->wall[WE] = mlx_texture_to_image(s->mlx.mlx_cub, s->png[WE]);
	mlx_delete_texture(s->png[WE]);
	if (!s->wall[SO] || !s->wall[NO] || !s->wall[EA] || !s->wall[WE])
		error_msg("Fail loading texture to image.");
}

void	draw_textures(t_cub3d *s, mlx_image_t *tex, int x)
{
	int			y;
	uint32_t	c;

	y = s->texturing.drawstart;
	while (y < s->texturing.drawend)
	{
		s->texturing.texy = (int)s->texturing.texpos & (tex->height - 1);
		s->texturing.texpos += s->texturing.step;
		c = put_pixel_color(tex, s->texturing.texx, s->texturing.texy);
		c = switch_channels(c);
		mlx_put_pixel(s->mlx.window, x, y, c);
		y++;
	}
}

void	draw_walls(t_cub3d *s, int x)
{
	s->rayc.lineheight = (int)((HEIGHT) / s->rayc.perpwalldist);
	s->texturing.drawstart = (-s->rayc.lineheight / 2) + (HEIGHT / 2) + PITCH;
	if (s->texturing.drawstart < 0)
		s->texturing.drawstart = 0;
	s->texturing.drawend = (s->rayc.lineheight / 2) + (HEIGHT / 2) + PITCH;
	if (s->texturing.drawend >= HEIGHT)
		s->texturing.drawend = HEIGHT - 1;
	texturing_calculations(s, x);
}

void	background_hook(void *param)
{
	t_cub3d	*data;
	int		i;

	data = param;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (i < WIDTH * (HEIGHT / 1.8))
			mlx_put_pixel(data->mlx.window, i, 0, data->ceiling);
		else if (i > WIDTH * (HEIGHT / 1.8))
			mlx_put_pixel(data->mlx.window, i, 0, data->floor);
		i++;
	}
}
