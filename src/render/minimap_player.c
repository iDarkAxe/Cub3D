/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:26 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/25 15:41:29 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void	render_line_with_offset(t_data *data, t_pos2 pos, float offset,
	int color)
{
	static const int	length = MINIMAP_PLAYER_SIZE
		* MINIMAP_LINE_OF_SIGHT_FACTOR;
	t_vec2				vec;
	t_pos2				dst;

	vec.x = cos(data->player.angle + offset);
	vec.y = sin(data->player.angle + offset);
	dst.x = pos.x + vec.x * length;
	dst.y = pos.y + vec.y * length;
	cubmlx_putline(data, pos, dst, color);
}

void	cubmlx_render_minimap_player(t_data *data)
{
	t_pos2	pos;
	t_pos2	rect;

	pos.x = MINIMAP_TILE_SIZE * (int)((MINIMAP_NUM_TILES_X >> 1) + 0.5f)
		- (MINIMAP_PLAYER_SIZE >> 1);
	pos.y = MINIMAP_TILE_SIZE * (int)((MINIMAP_NUM_TILES_Y >> 1) + 0.5f)
		- (MINIMAP_PLAYER_SIZE >> 1);
	rect = (t_pos2){MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE};
	cubmlx_putrect(data, pos, rect, MINIMAP_PLAYER_COLOR);
	pos.x += MINIMAP_PLAYER_SIZE >> 1;
	pos.y += MINIMAP_PLAYER_SIZE >> 1;
	if (data->input.fov)
	{
		render_line_with_offset(data, pos, -data->player.fov * 0.5f,
			MINIMAP_PLAYER_CONE_SIGHT_COLOR);
		render_line_with_offset(data, pos, data->player.fov * 0.5f,
			MINIMAP_PLAYER_CONE_SIGHT_COLOR);
	}
	else
		render_line_with_offset(data, pos, 0,
			MINIMAP_PLAYER_LINE_SIGHT_COLOR);
}
