/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/23 16:17:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cubtest.h"
#include <math.h>

void	solve_collision_x(t_cub *cub, float x_vel)
{
	static const float	player_half_square = 0.125f * 0.5f;
	float				left;
	float				right;
	int					map_i;

	left = cub->player.pos.x - player_half_square;
	right = cub->player.pos.x + player_half_square;
	if (x_vel > 0)
	{
		map_i = (int)right + (int)cub->player.pos.y * cub->map->width;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.x = (float)(int)right - player_half_square;
	}
	else
	{
		map_i = (int)left + (int)cub->player.pos.y * cub->map->width;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.x = (float)(int)(left + 1) + player_half_square;
	}
}

void	solve_collision_y(t_cub *cub, float y_vel)
{
	static const float	player_half_square = 0.125f * 0.5f;
	float				top;
	float				bottom;
	int					map_i;

	top = cub->player.pos.y - player_half_square;
	bottom = cub->player.pos.y + player_half_square;
	if (y_vel > 0)
	{
		map_i = (int)bottom * cub->map->width + (int)cub->player.pos.x;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.y = (float)(int)bottom - player_half_square;
	}
	else
	{
		map_i = (int)top * cub->map->width + (int)cub->player.pos.x;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.y = (float)(int)(top + 1) + player_half_square;
	}
}
