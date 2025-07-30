/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/30 12:07:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"

static void	update_camera(t_data *data)
{
	static const float	two_pi = (float)(PI)*2.f;

	if (data->input.turn_left)
		data->player.angle -= 0.015f;
	if (data->input.turn_right)
		data->player.angle += 0.015f;
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
		vel.y += 0.025f;
	if (data->input.bckwd)
		vel.y -= 0.025f;
	if (data->input.left)
		vel.x += 0.015f;
	if (data->input.right)
		vel.x -= 0.015f;
	vel = vec2rotate(vel, data->player.angle - half_pi);
	data->player.pos.x += vel.x;
	if (vel.x != 0.f)
		solve_collision_x(data, vel.x);
	data->player.pos.y += vel.y;
	if (vel.y != 0.f)
		solve_collision_y(data, vel.y);
	update_camera(data);
}

// TODO: add back view bobbing. Thank you, merge conflict
void	cub_player_update(t_data *data)
{
	update_movement(data);
}
