/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:02:41 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/20 16:28:25 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	get_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

// Probably a bug on linux, but color from textures didn't load smooth,
// has to swap some channels to get it correct. **TEST ON MAC**

uint32_t	switch_channels(uint32_t color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	a = get_a(color);
	b = get_b(color);
	g = get_g(color);
	r = get_r(color);
	return (get_rgba(a, b, g, r));
}

void	load_color(char **rgb, uint32_t *color)
{
	if (ft_atoi(rgb[0]) >= 0 && ft_atoi(rgb[0]) <= 255 && ft_atoi(rgb[1]) >= 0
		&& ft_atoi(rgb[1]) <= 255 && ft_atoi(rgb[2]) >= 0
		&& ft_atoi(rgb[2]) <= 255)
		*color = get_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		error_msg("RGB Color out of range.");
}

void	create_color(t_cub3d *s, int y)
{
	int		x;
	char	**rgb;

	x = 0;
	while (!ft_isdigit(s->map[y][x]))
		x++;
	rgb = ft_split(s->map[y] + x, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
		error_msg("RGB Color is missing.");
	if (!ft_strncmp("C ", s->map[y], 2))
	{
		load_color(rgb, &s->ceiling);
		free_map(rgb);
	}
	else if (!ft_strncmp("F ", s->map[y], 2))
	{
		load_color(rgb, &s->floor);
		free_map(rgb);
	}
}
