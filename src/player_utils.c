/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/08 16:18:42 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void	solve_collision_x(t_data *data, float x_vel)
{
	static const float	player_half_square = 0.125f * 0.5f;
	float				left;
	float				right;
	int					map_i;

	left = data->player.pos.x - player_half_square;
	right = data->player.pos.x + player_half_square;
	if (x_vel > 0)
	{
		map_i = (int)right + (int)data->player.pos.y * data->map.map->width;
		if (data->map.map->walls[map_i] > 0)
			data->player.pos.x = (float)(int)right - player_half_square;
	}
	else
	{
		map_i = (int)left + (int)data->player.pos.y * data->map.map->width;
		if (data->map.map->walls[map_i] > 0)
			data->player.pos.x = (float)(int)(left + 1) + player_half_square;
	}
}

void	solve_collision_y(t_data *data, float y_vel)
{
	static const float	player_half_square = 0.125f * 0.5f;
	float				top;
	float				bottom;
	int					map_i;

	top = data->player.pos.y - player_half_square;
	bottom = data->player.pos.y + player_half_square;
	if (y_vel > 0)
	{
		map_i = (int)bottom * data->map.map->width + (int)data->player.pos.x;
		if (data->map.map->walls[map_i] > 0)
			data->player.pos.y = (float)(int)bottom - player_half_square;
	}
	else
	{
		map_i = (int)top * data->map.map->width + (int)data->player.pos.x;
		if (data->map.map->walls[map_i] > 0)
			data->player.pos.y = (float)(int)(top + 1) + player_half_square;
	}
}
