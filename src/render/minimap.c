/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:50:16 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/08 15:46:55 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

void	cubmlx_render_minimap_player(t_data *data);

static void	render_tile(t_data *data, t_pos2 pos, int x, int y)
{
	static const t_pos2	max_size = {(MINIMAP_TILES_X - 1) * MINIMAP_TILE_SIZE,
		(MINIMAP_TILES_Y - 1) * MINIMAP_TILE_SIZE};
	t_pos2				rect;

	rect = (t_pos2){MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE};
	(void)max_size;
	if (pos.x + rect.x >= max_size.x)
		rect.x = max_size.x - pos.x;
	if (pos.y + rect.y >= max_size.y)
		rect.y = max_size.y - pos.y;
	if (y >= 0 && x >= 0
		&& x < (int)data->map.map->width
		&& y < (int)data->map.map->height
		&& data->map.map->walls[y * data->map.map->width + x])
		cubmlx_putrect(data, pos, rect, MINIMAP_WALL_COLOR);
	else
		cubmlx_putrect(data, pos, rect, MINIMAP_FLOOR_COLOR);
}

// NOTE: DO NOT ADD NULL CHECK
static void	dynamic_minimap(t_data *data, t_pos2 start_range, t_pos2 end_range,
	t_pos2 offset)
{
	static const t_pos2	max_size = {MINIMAP_TILES_X * MINIMAP_TILE_SIZE,
		MINIMAP_TILES_Y * MINIMAP_TILE_SIZE};
	int					x;
	int					y;
	t_pos2				pos;

	y = start_range.y;
	while (y < end_range.y)
	{
		if (y >= max_size.y)
			break ;
		x = start_range.x;
		while (x < end_range.x)
		{
			if (x >= max_size.x)
				break ;
			pos.x = (x - start_range.x) * MINIMAP_TILE_SIZE - offset.x;
			pos.y = (y - start_range.y) * MINIMAP_TILE_SIZE - offset.y;
			render_tile(data, pos, x, y);
			x++;
		}
		y++;
	}
}

// NOTE: DO NOT ADD NULL CHECK
void	cub_render_minimap(t_data *data)
{
	t_pos2	start_range;
	t_pos2	end_range;
	t_vec2	offset;
	t_pos2	ioffset;
	t_vec2	player;

	offset = data->player.pos;
	start_range.x = (int)floor(offset.x) - (MINIMAP_TILES_X >> 1);
	start_range.y = (int)floor(offset.y) - (MINIMAP_TILES_Y >> 1);
	end_range.x = (int)ceil(offset.x) + (MINIMAP_TILES_X >> 1);
	end_range.y = (int)ceil(offset.y) + (MINIMAP_TILES_Y >> 1);
	offset.x = offset.x - floor(offset.x);
	offset.y = offset.y - floor(offset.y);
	ioffset.x = (int)(offset.x * MINIMAP_TILE_SIZE);
	ioffset.y = (int)(offset.y * MINIMAP_TILE_SIZE);
	dynamic_minimap(data, start_range, end_range, ioffset);
	player.x = 6 * MINIMAP_TILE_SIZE + offset.x;
	player.y = 6 * MINIMAP_TILE_SIZE + offset.y;
	cubmlx_render_minimap_player(data);
}
