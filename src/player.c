/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/23 14:42:49 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cubtest.h"

void	solve_collision_x(t_cub *cub, float x_vel);
void	solve_collision_y(t_cub *cub, float y_vel);

static void	update_camera(t_cub *cub)
{
	if (cub->input.turn_left && cub->input.turn_right)
		;
	else if (cub->input.turn_left)
		cub->player.angle -= 0.01f;
	else if (cub->input.turn_right)
		cub->player.angle += 0.01f;
	if (cub->player.angle >= (2.f * PI))
		cub->player.angle -= (2.f * PI);
	if (cub->player.angle < 0.f)
		cub->player.angle += (2.f * PI);
}

// TODO: Needs to implement a left and right movement
static void	update_movement(t_cub *cub)
{
	t_vec2	vel;

	vel = (t_vec2){0, 0};
	if (cub->input.fwd)
		vel.y += 0.01f;
	if (cub->input.bckwd)
		vel.y -= 0.01f;
	if (cub->input.left)
		vel.x += 0.01f;
	if (cub->input.right)
		vel.x -= 0.01f;
	vel = vec2rotate(vel, cub->player.angle - PI * 0.5f);
	cub->player.pos.x += vel.x;
	if (vel.x != 0.f)
		solve_collision_x(cub, vel.x);
	cub->player.pos.y += vel.y;
	if (vel.y != 0.f)
		solve_collision_y(cub, vel.y);
	update_camera(cub);
}

// TODO: add back view bobbing. Thank you, merge conflict
void	cub_player_update(t_cub *cub)
{
	update_movement(cub);
}
