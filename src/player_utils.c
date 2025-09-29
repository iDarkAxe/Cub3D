/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/27 01:04:22 by ppontet          ###   ########lyon.fr   */
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

void	resolve_collision_steps(t_data *data, float vel_x, float vel_y)
{
	float	max_vel;
	int		steps;
	float	step_x;
	float	step_y;
	int		i;

	max_vel = fmaxf(fabsf(vel_x), fabsf(vel_y));
	steps = (int)(max_vel / 0.9f) + 1;
	step_x = vel_x / (float)steps;
	step_y = vel_y / (float)steps;
	i = 0;
	while (i < steps)
	{
		data->player.pos.x += step_x;
		if (step_x != 0.f && data->input.collision)
			solve_collision_x(data, step_x);
		data->player.pos.y += step_y;
		if (step_y != 0.f && data->input.collision)
			solve_collision_y(data, step_y);
		i++;
	}
}
