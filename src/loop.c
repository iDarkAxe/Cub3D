/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:36:48 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/23 14:18:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cubtest.h"
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
	t_cub	*cub;

	cub = (t_cub *)param;
	cub_player_update(cub);
	cub_render(cub);
	return (1);
}

void	cub_loop(t_cub *cub)
{
	mlx_hook(cub->mlx.win, DestroyNotify, StructureNotifyMask, &mlx_loop_end,
		cub->mlx.mlx);
	mlx_hook(cub->mlx.win, KeyPress, KeyPressMask, &cub_keydown_hook,
		&cub->input);
	mlx_hook(cub->mlx.win, KeyRelease, KeyReleaseMask, &cub_keyup_hook,
		&cub->input);
	mlx_loop_hook(cub->mlx.mlx, &loop_hook, cub);
	mlx_loop(cub->mlx.mlx);
}
