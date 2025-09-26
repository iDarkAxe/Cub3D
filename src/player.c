/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/27 01:04:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void	update_camera(t_data *data)
{
	static const float	two_pi = (float)(PI)*2.f;
	float				turn_amount;

	turn_amount = 0.f;
	if (data->input.turn_left)
		turn_amount -= MOVEMENT_SPEED_TURNING;
	if (data->input.turn_right)
		turn_amount += MOVEMENT_SPEED_TURNING;
	if (data->input.mouse_input)
	{
		turn_amount += data->input.delta_mouse_x * MOUSE_SENSITIVITY_FACTOR;
		data->input.mouse_input = 0;
	}
	data->player.angle += turn_amount;
	if (data->player.angle >= (two_pi))
		data->player.angle -= (two_pi);
	if (data->player.angle < 0.f)
		data->player.angle += (two_pi);
}

static void	update_movement(t_data *data)
{
	static const float	half_pi = (float)(PI)*0.5f;
	t_vec2				vel;

	vel = (t_vec2){0, 0};
	if (data->input.fwd)
		vel.y += MOVEMENT_SPEED_FWD_BWD;
	if (data->input.bckwd)
		vel.y -= MOVEMENT_SPEED_FWD_BWD;
	if (data->input.left)
		vel.x += MOVEMENT_SPEED_LEFT_RIGHT;
	if (data->input.right)
		vel.x -= MOVEMENT_SPEED_LEFT_RIGHT;
	vel = vec2rotate(vel, data->player.angle - half_pi);
	if (MOVEMENT_SPEED_FWD_BWD < 1.0f && MOVEMENT_SPEED_LEFT_RIGHT < 1.0f)
	{
		data->player.pos.x += vel.x;
		if (vel.x != 0.f && data->input.collision)
			solve_collision_x(data, vel.x);
		data->player.pos.y += vel.y;
		if (vel.y != 0.f && data->input.collision)
			solve_collision_y(data, vel.y);
	}
	else
		resolve_collision_steps(data, vel.x, vel.y);
	update_camera(data);
}

// TODO: add back view bobbing. Thank you, merge conflict
void	cub_player_update(t_data *data)
{
	update_movement(data);
}
