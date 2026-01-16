/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:26 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/16 19:12:54 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void	render_fov_zone(t_data *data, t_pos2 origin);

void	cubmlx_render_minimap_player(t_data *data)
{
	t_pos2	pos;
	t_pos2	rect;
	int		dist;
	t_pos2	end;

	pos.x = MINIMAP_TILE_SIZE * (int)((MINIMAP_NUM_TILES_X >> 1) + 0.5f)
		- (MINIMAP_PLAYER_SIZE >> 1);
	pos.y = MINIMAP_TILE_SIZE * (int)((MINIMAP_NUM_TILES_Y >> 1) + 0.5f)
		- (MINIMAP_PLAYER_SIZE >> 1);
	rect = (t_pos2){MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE};
	cubmlx_putrect(data, pos, rect, MINIMAP_PLAYER_COLOR);
	pos.x += MINIMAP_PLAYER_SIZE >> 1;
	pos.y += MINIMAP_PLAYER_SIZE >> 1;
	if (data->input.fov)
		render_fov_zone(data, pos);
	else
	{
		dist = minimap_raycast(data, data->player.angle);
		end = minimap_ray_endpoint(data, pos, data->player.angle, dist);
		cubmlx_putline(data, pos, end, MINIMAP_PLAYER_CONE_SIGHT_COLOR);
	}
}

void	render_fov_zone(t_data *data, t_pos2 origin)
{
	float	angle;
	float	step;
	float	dist;
	t_pos2	end;

	step = data->player.fov / MINIMAP_STEP_ANGLE_DIV;
	angle = data->player.angle - data->player.fov * 0.5f;
	while (angle <= data->player.angle + data->player.fov * 0.5f)
	{
		dist = minimap_raycast(data, angle);
		end = minimap_ray_endpoint(data, origin, angle, dist);
		cubmlx_putline(data, origin, end, MINIMAP_PLAYER_CONE_SIGHT_COLOR);
		angle += step;
	}
}
