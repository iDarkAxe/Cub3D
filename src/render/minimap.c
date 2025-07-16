/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:50:16 by rdesprez          #+#    #+#             */
/*   Updated: 2025/06/25 12:55:06 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

static void	render_square(t_cub *cub, t_pos2 pos, int size, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			cubmlx_putpixel(cub->mlx, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

static void	render_minimap_player(t_cub *cub, int tile_size)
{
	t_pos2	pos;
	t_pos2	pos2;

	pos.x = cub->player.pos.x * tile_size - 2;
	pos.y = cub->player.pos.y * tile_size - 2;
	render_square(cub, pos, 4, 0xff00ff00);
	pos.x = (int)(cub->player.pos.x * tile_size);
	pos.y = (int)(cub->player.pos.y * tile_size);
	pos2.x = 8 * cos(cub->player.angle) + cub->player.pos.x * tile_size;
	pos2.y = 8 * sin(cub->player.angle) + cub->player.pos.y * tile_size;
	cubmlx_putline(cub->mlx, pos, pos2, 0xff00ff00);
}

void	cub_render_minimap(t_cub *cub)
{
	size_t		x;
	size_t		y;
	t_pos2		pos;
	const int	tile_size = 16;

	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		pos.y = y * tile_size;
		while (x < cub->map->width)
		{
			pos.x = x * tile_size;
			if (cub->map->walls[y * cub->map->width + x])
				render_square(cub, pos, tile_size, 0xffffffff);
			else
				render_square(cub, pos, tile_size, 0xff000000);
			x++;
		}
		y++;
	}
	render_minimap_player(cub, tile_size);
}
