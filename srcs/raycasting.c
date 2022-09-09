/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:49:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/09 18:09:50 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_cub3d *s, int x, int32_t color_test)
{
	int	drawstart;
	int	drawend;

	s->rayc.lineheight = (int)((HEIGHT) / s->rayc.perpwalldist);
	drawstart = (-(s->rayc.lineheight) / 2) + (HEIGHT / 2);
	if (drawstart < 0)
		drawstart = 0;
	drawend = (s->rayc.lineheight / 2) + (HEIGHT / 2);
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;
	draw_verline(s->mlx.window, drawstart, drawend, x, color_test);
}

void	draw_verline(mlx_image_t *screen, int y1, int y2, int x,
		int32_t color_test)
{
	int	start;
	int	end;

	start = y1;
	end = y2;
	while (start < end)
	{
		mlx_put_pixel(screen, x, start, color_test);
		start++;
	}
}

void	perform_dda(t_raycast *r, char **map)
{
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
		if (map[abs(r->mapy)][abs(r->mapx)] == '1')
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
	r->deltadistx = sqrt(1 + (r->raydiry * r->raydiry) / (r->raydirx
				* r->raydirx));
	r->deltadisty = sqrt(1 + (r->raydirx * r->raydirx) / (r->raydiry
				* r->raydiry));
	r->hit = 0;
}

void	raycasting(void *param)
{
	t_cub3d	*s;
	int		x;
	int32_t	color_test;

	x = 0;
	s = param;
	color_test = get_rgb(255, 130, 0);
	while (x < s->mlx.width)
	{
		raycast_init(&s->rayc, x);
		calculate_step(s);
		perform_dda(&s->rayc, s->map);
		if (s->rayc.side == 0)
			s->rayc.perpwalldist = (s->rayc.sidedistx - s->rayc.deltadistx);
		else
			s->rayc.perpwalldist = (s->rayc.sidedisty - s->rayc.deltadisty);
		if (s->rayc.side == 1)
			color_test = get_rgb(60, 190, 215);
		draw_walls(s, x, color_test);
		x++;
	}
}
