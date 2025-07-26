/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:36:48 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 15:41:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "ft_keys.h"
#include "mlx.h"
#include <X11/X.h>

void		ft_print_key(int keycode);

static void	set_key(int keycode, t_input *input, bool set)
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

// TODO : Needs to change param as it can't modify mlx for closing window
static int	cub_keydown_hook(int keycode, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	if (DEBUG_PRINT_KEYCODE == 1)
		ft_print_key(keycode);
	set_key(keycode, input, true);
	return (0);
}

static int	cub_keyup_hook(int keycode, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	set_key(keycode, input, false);
	return (0);
}

static int	loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cub_player_update(data);
	cub_render(data);
	return (1);
}

void	cub_loop(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask, &mlx_loop_end,
		data->mlx.mlx_ptr);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, &cub_keydown_hook,
		&data->input);
	mlx_hook(data->mlx.win_ptr, KeyRelease, KeyReleaseMask, &cub_keyup_hook,
		&data->input);
	mlx_loop_hook(data->mlx.mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx.mlx_ptr);
}
