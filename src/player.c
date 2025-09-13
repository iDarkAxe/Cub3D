/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/13 15:38:47 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "mlx.h"

static void	update_camera(t_data *data)
{
	static const float	two_pi = (float)(PI)*2.f;
	float				turn_amount;

	turn_amount = 0.f;
	if (data->input.turn_left)
		turn_amount -= TURNING_SPEED;
	if (data->input.turn_right)
		turn_amount += TURNING_SPEED;
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
		vel.y += 0.025f;
	if (data->input.bckwd)
		vel.y -= 0.025f;
	if (data->input.left)
		vel.x += 0.015f;
	if (data->input.right)
		vel.x -= 0.015f;
	vel = vec2rotate(vel, data->player.angle - half_pi);
	data->player.pos.x += vel.x;
	if (vel.x != 0.f && data->input.collision)
		solve_collision_x(data, vel.x);
	data->player.pos.y += vel.y;
	if (vel.y != 0.f && data->input.collision)
		solve_collision_y(data, vel.y);
	update_camera(data);
}

static void	key_door_logic(t_player *player, t_map_raoul *map, void *mlx_ptr)
{
	if (map->key.x > -1)
	{
		if ((int)player->pos.x == map->key.x
			&& (int)player->pos.y == map->key.y)
		{
			map->walls[map->width * map->key.y + map->key.x] = 0;
			map->key = (t_pos2){-1, -1};
		}
	}
	if (map->door.x > -1 && map->key.x == -1)
	{
		if ((int)player->pos.x == map->door.x
			&& (int)player->pos.y == map->door.y)
			mlx_loop_end(mlx_ptr);
	}
}

// TODO: add back view bobbing. Thank you, merge conflict
void	cub_player_update(t_data *data)
{
	update_movement(data);
	key_door_logic(&data->player, data->map.map, data->mlx.mlx_ptr);
}
