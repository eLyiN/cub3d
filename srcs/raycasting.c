/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:49:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/19 20:05:02 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_cub3d *s, int x)
{
	int	drawstart;
	int	drawend;

	s->rayc.lineheight = (int)((HEIGHT) / s->rayc.perpwalldist);
	drawstart = (-s->rayc.lineheight / 2) + (HEIGHT / 2);
	if (drawstart < 0)
		drawstart = 0;
	drawend = (s->rayc.lineheight / 2) + (HEIGHT / 2);
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;
	texturing_calculations(s, drawstart, drawend, x);
}

void	perform_dda(t_raycast *r, char **map)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (map[r->mapy][r->mapx] == '1')
			r->hit = 1;
	}
}

void	calculate_step(t_cub3d *s)
{
	if (s->rayc.raydirx < 0)
	{
		s->rayc.stepx = -1;
		s->rayc.sidedistx = (s->rayc.posx - s->rayc.mapx) * s->rayc.deltadistx;
	}
	else
	{
		s->rayc.stepx = 1;
		s->rayc.sidedistx = (s->rayc.mapx + 1.0 - s->rayc.posx)
			* s->rayc.deltadistx;
	}
	if (s->rayc.raydiry < 0)
	{
		s->rayc.stepy = -1;
		s->rayc.sidedisty = (s->rayc.posy - s->rayc.mapy) * s->rayc.deltadisty;
	}
	else
	{
		s->rayc.stepy = 1;
		s->rayc.sidedisty = (s->rayc.mapy + 1.0 - s->rayc.posy)
			* s->rayc.deltadisty;
	}
}

void	raycast_init(t_raycast *r, int x)
{
	r->camerax = (2 * x) / ((double)WIDTH - 1);
	r->raydirx = r->dirx + r->planex * r->camerax;
	r->raydiry = r->diry + r->planey * r->camerax;
	r->mapx = (int)r->posx;
	r->mapy = (int)r->posy;
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
}

void	raycasting(void *param)
{
	t_cub3d	*s;

	s = param;
	s->rayc.pixel = 0;
	while (s->rayc.pixel < s->mlx.width)
	{
		raycast_init(&s->rayc, s->rayc.pixel);
		calculate_step(s);
		perform_dda(&s->rayc, s->map);
		if (s->rayc.side == 0)
			s->rayc.perpwalldist = (s->rayc.sidedistx - s->rayc.deltadistx);
		else
			s->rayc.perpwalldist = (s->rayc.sidedisty - s->rayc.deltadisty);
		draw_walls(s, s->rayc.pixel);
		s->rayc.pixel++;
	}
}
