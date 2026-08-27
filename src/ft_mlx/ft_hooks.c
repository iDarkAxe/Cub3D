/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:16:53 by ppontet           #+#    #+#             */
/*   Updated: 2025/12/18 21:50:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_print.h"
#include "MLX42/MLX42.h"

// These functions are not used with MLX42 anymore
// They are kept for reference but should not be called

int	cub_keydown_hook(keys_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (DEBUG_PRINT_KEYCODE == 1)
		ft_print_key((int)key);
	if (key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx.win_ptr);
	if (key == MLX_KEY_DOWN || key == MLX_KEY_UP)
		change_fov(data, (int)key);
	if (ENABLE_FILTERS)
		change_filter(data, (int)key);
	set_key((int)key, &data->input, true);
	toggle_key((int)key, &data->input);
	return (0);
}

int	cub_keyup_hook(keys_t key, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	input->needs_render = 1;
	set_key((int)key, input, false);
	return (0);
}

static int	interpret_mouse_mouvement(t_data *data, double x, double y, int click)
{
	(void)click;
	if (data->input.skip_next_mouse_input)
	{
		data->input.skip_next_mouse_input = 0;
		return (0);
	}
	data->input.delta_mouse_x = (int)x - (data->mlx.win_size.x >> 1);
	data->input.mouse_input = 1;
	return (0);
}

int	cub_mouse_hook(double x, double y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	return (interpret_mouse_mouvement(data, x, y, 0));
}

int	cub_mouse_click_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_data	*data;

	(void)action;
	(void)mods;
	data = (t_data *)param;
	return (interpret_mouse_mouvement(data, (double)data->mlx.mouse_x, (double)data->mlx.mouse_y, (int)button));
}
