/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:04:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/29 15:27:00 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "ft_keys.h"
#include <stdbool.h>

void	set_key(int keycode, t_input *input, bool set)
{
	if (keycode == KEY_W)
		input->fwd = set;
	else if (keycode == KEY_S)
		input->bckwd = set;
	else if (keycode == KEY_A)
		input->left = set;
	else if (keycode == KEY_D)
		input->right = set;
	else if (keycode == KEY_ARROW_LEFT)
		input->turn_left = set;
	else if (keycode == KEY_ARROW_RIGHT)
		input->turn_right = set;
}

void	toggle_key(int keycode, t_input *input)
{
	if (keycode == KEY_C)
	{
		if (input->collision)
			input->collision = false;
		else
			input->collision = true;
	}
	else if (keycode == KEY_M)
	{
		if (input->minimap)
			input->minimap = false;
		else
			input->minimap = true;
	}
	else if (keycode == KEY_F)
	{
		if (input->fov)
			input->fov = false;
		else
			input->fov = true;
	}
}

bool	is_mv_key(enum e_movement expected, int keycode)
{
	if (expected == MV_UP && ((keycode) == KEY_ARROW_UP || (keycode) == KEY_W))
		return (true);
	if (expected == MV_LEFT && ((keycode) == KEY_ARROW_LEFT
			|| (keycode) == KEY_A))
		return (true);
	if (expected == MV_RIGHT && ((keycode) == KEY_ARROW_RIGHT
			|| (keycode) == KEY_D))
		return (true);
	if (expected == MV_DOWN && ((keycode) == KEY_ARROW_DOWN
			|| (keycode) == KEY_S))
		return (true);
	return (false);
}

void	change_fov(t_data *data, int keycode)
{
	if (data->player.fov > 0.01f && keycode == KEY_ARROW_DOWN)
		data->player.fov -= 0.01f;
	else if (keycode == KEY_ARROW_UP)
		data->player.fov += 0.01f;
	if (data->player.fov < 0.0f)
		data->player.fov = 0.0f;
	else if (data->player.fov >= PI)
		data->player.fov = PI;
}
