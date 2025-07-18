/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:50:16 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/18 12:00:55 by ppontet          ###   ########lyon.fr   */
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
			cubmlx_putpixel(cub, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

#if ENABLE_FIELD_OF_VIEW == 1

void	render_line_of_sight(t_cub *cub, t_pos2 pos, int tile_size)
{
	t_pos2	line_left;
	t_pos2	line_right;

	line_left.x = 8 * cos(cub->player.angle - cub->player.fov * 0.5)
		+ cub->player.pos.x * tile_size;
	line_left.y = 8 * sin(cub->player.angle - cub->player.fov * 0.5)
		+ cub->player.pos.y * tile_size;
	line_right.x = 8 * cos(cub->player.angle + cub->player.fov * 0.5)
		+ cub->player.pos.x * tile_size;
	line_right.y = 8 * sin(cub->player.angle + cub->player.fov * 0.5)
		+ cub->player.pos.y * tile_size;
	cubmlx_putline(cub, pos, line_left,
		MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR);
	cubmlx_putline(cub, pos, line_right,
		MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR);
}

#else

void	render_line_of_sight(t_cub *cub, t_pos2 pos, int tile_size)
{
	t_pos2	len;

	len.x = 8 * cos(cub->player.angle) + cub->player.pos.x * tile_size;
	len.y = 8 * sin(cub->player.angle) + cub->player.pos.y * tile_size;
	cubmlx_putline(cub, pos, len, MINIMAP_PLAYER_LINE_OF_SIGHT_COLOR);
}

#endif

static void	render_minimap_player(t_cub *cub, int tile_size)
{
	t_pos2	pos;

	pos.x = cub->player.pos.x * tile_size - 2;
	pos.y = cub->player.pos.y * tile_size - 2;
	render_square(cub, pos, 4, MINIMAP_PLAYER_COLOR);
	pos.x = (int)(cub->player.pos.x * tile_size);
	pos.y = (int)(cub->player.pos.y * tile_size);
	render_line_of_sight(cub, pos, tile_size);
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
				render_square(cub, pos, tile_size, MINIMAP_WALL_COLOR);
			else
				render_square(cub, pos, tile_size, MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
	render_minimap_player(cub, tile_size);
}
