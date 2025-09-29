/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:16:53 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/29 15:11:45 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_print.h"
#include "mlx.h"
#include <X11/X.h>
#include "maze.h"
#include "filter.h"

int	cub_keydown_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (DEBUG_PRINT_KEYCODE == 1)
		ft_print_key(keycode);
	if (keycode == KEY_ESCAPE)
	{
		mlx_loop_end(data->mlx.mlx_ptr);
		return (0);
	}
	if (keycode == KEY_ARROW_DOWN || keycode == KEY_ARROW_UP)
		change_fov(data, keycode);
	if (ENABLE_FILTERS)
		change_filter(data, keycode);
	set_key(keycode, &data->input, true);
	toggle_key(keycode, &data->input);
	return (0);
}

int	cub_keyup_hook(int keycode, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	set_key(keycode, input, false);
	return (0);
}

static int	interpret_mouse_mouvement(t_data *data, int x, int y, int click)
{
	(void)y;
	(void)click;
	if (data->input.skip_next_mouse_input)
	{
		data->input.skip_next_mouse_input = 0;
		return (0);
	}
	data->input.delta_mouse_x = x - (data->mlx.win_size.x >> 1);
	data->input.mouse_input = 1;
	return (0);
}

int	cub_mouse_hook(int x, int y, void *param)
{
	t_data	*data;

	(void)y;
	data = (t_data *)param;
	return (interpret_mouse_mouvement(data, x, y, 0));
}

int	cub_mouse_click_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)y;
	(void)button;
	data = (t_data *)param;
	return (interpret_mouse_mouvement(data, x, y, button));
}
