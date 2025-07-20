/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/20 18:04:37 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

static void	solve_collision_x(t_cub *cub, float x_vel)
{
	const float	player_square = 0.125f;
	float		left;
	float		right;
	int			map_i;

	left = cub->player.pos.x - player_square * 0.5f;
	right = cub->player.pos.x + player_square * 0.5f;
	if (x_vel > 0)
	{
		map_i = (int)right + (int)cub->player.pos.y * cub->map->width;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.x = (float)(int)right - player_square * 0.5f;
	}
	else
	{
		map_i = (int)left + (int)cub->player.pos.y * cub->map->width;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.x = (float)(int)(left + 1) + player_square * 0.5f;
	}
}

static void	solve_collision_y(t_cub *cub, float y_vel)
{
	const float	player_square = 0.125f;
	float		top;
	float		bottom;
	int			map_i;

	top = cub->player.pos.y - player_square * 0.5f;
	bottom = cub->player.pos.y + player_square * 0.5f;
	if (y_vel > 0)
	{
		map_i = (int)bottom * cub->map->width + (int)cub->player.pos.x;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.y = (float)(int)bottom - player_square * 0.5f;
	}
	else
	{
		map_i = (int)top * cub->map->width + (int)cub->player.pos.x;
		if (cub->map->walls[map_i] > 0)
			cub->player.pos.y = (float)(int)(top + 1) + player_square * 0.5f;
	}
}

static void	update_movement(t_cub *cub)
{
	t_vec2	vel;

	vel = (t_vec2){0, 0};
	if (cub->input.fwd)
		vel = (t_vec2){0.01f * cos(cub->player.angle),
			0.01f * sin(cub->player.angle)};
	if (cub->input.bckwd)
		vel = (t_vec2){-0.01f * cos(cub->player.angle),
			-0.01f * sin(cub->player.angle)};
	cub->player.pos.x += vel.x;
	if (vel.x != 0.f)
		solve_collision_x(cub, vel.x);
	cub->player.pos.y += vel.y;
	if (vel.y != 0.f)
		solve_collision_y(cub, vel.y);
	if (cub->input.left)
		cub->player.angle -= 0.01f;
	if (cub->input.right)
		cub->player.angle += 0.01f;
	if (cub->player.angle >= (2.f * PI))
		cub->player.angle -= (2.f * PI);
	if (cub->player.angle < 0.f)
		cub->player.angle += (2.f * PI);
}

// TODO: add back view bobbing. Thank you, merge conflict
void	cub_player_update(t_cub *cub)
{
	update_movement(cub);
}
