/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:26:21 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 17:22:02 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	set_pos_ini_n(t_raycast *r, int x, int y)
{
	r->posx = x;
	r->posy = y;
	r->dirx = -1;
	r->diry = 0;
	r->planex = 0;
	r->planey = 0.66;
	return (true);
}

bool	set_pos_ini_e(t_raycast *r, int x, int y)
{
	r->posx = x;
	r->posy = y;
	r->dirx = 0;
	r->diry = 1;
	r->planex = 0.66;
	r->planey = 0;
	return (true);
}

bool	set_pos_ini_s(t_raycast *r, int x, int y)
{
	r->posx = x;
	r->posy = y;
	r->dirx = 1;
	r->diry = 0;
	r->planex = 0;
	r->planey = -0.66;
	return (true);
}

bool	set_pos_ini_w(t_raycast *r, int x, int y)
{
	r->posx = x;
	r->posy = y;
	r->dirx = 0;
	r->diry = -1;
	r->planex = -0.66;
	r->planey = 0;
	return (true);
}

void	check_pos_ini(t_cub3d *s)
{
	int	x;
	int	y;
	int	pos_ini;

	y = map_start(s->map);
	pos_ini = 0;
	while (y < s->mapy)
	{
		x = -1;
		while (s->map[y][++x])
		{
			if (s->map[y][x] == 'N')
				pos_ini += set_pos_ini_n(&s->rayc, x, y);
			else if (s->map[y][x] == 'E')
				pos_ini += set_pos_ini_e(&s->rayc, x, y);
			else if (s->map[y][x] == 'S')
				pos_ini += set_pos_ini_s(&s->rayc, x, y);
			else if (s->map[y][x] == 'W')
				pos_ini += set_pos_ini_n(&s->rayc, x, y);
		}
		y++;
	}
	if (pos_ini > 1)
		error_msg("The map contains multiple starting positions.");
}
