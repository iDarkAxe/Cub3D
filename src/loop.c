/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:36:48 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/17 14:51:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <MLX42.h>
#include "filter.h"
#include "ft_keys.h"

#if SKIP_NO_MVMT == 1

static void	loop_hook(void *param)
{
	static t_pos2	half_win_size = {0};
	t_data			*data;

	data = (t_data *)param;
	if (half_win_size.x == 0)
	{
		half_win_size.x = data->mlx.win_size.x * 0.5f;
		half_win_size.y = data->mlx.win_size.y * 0.5f;
	}
	count_fps(1);
	data->input.skip_next_mouse_input = 1;
	mlx_set_mouse_pos(data->mlx.mlx_ptr, half_win_size.x, half_win_size.y);
	cub_player_update(data);
	if (data->input.needs_render == false)
		return;
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_image_to_window(data->mlx.mlx_ptr, data->mlx.backbuffer.img, 0, 0);
	data->input.needs_render = false;
}

#else

static void	loop_hook(void *param)
{
	static t_pos2	half_win_size = {0};
	t_data			*data;

	data = (t_data *)param;
	if (half_win_size.x == 0)
	{
		half_win_size.x = data->mlx.win_size.x * 0.5f;
		half_win_size.y = data->mlx.win_size.y * 0.5f;
	}
	count_fps(1);
	data->input.skip_next_mouse_input = 1;
	mlx_set_mouse_pos(data->mlx.mlx_ptr, half_win_size.x, half_win_size.y);
	cub_player_update(data);
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_image_to_window(data->mlx.mlx_ptr, data->mlx.backbuffer.img, 0, 0);
}

#endif

static void	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_close_window(data->mlx.mlx_ptr);
}

static void	handle_key(keys_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == MLX_KEY_ESCAPE)
		handle_close(data);
	if (key == MLX_KEY_DOWN || key == MLX_KEY_UP)
		change_fov(data, (int)key);
	if (ENABLE_FILTERS)
		change_filter(data, (int)key);
	set_key((int)key, &data->input, true);
	toggle_key((int)key, &data->input);
}

static void	handle_key_release(keys_t key, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	input->needs_render = 1;
	set_key((int)key, input, false);
}

static void	handle_mouse(double xpos, double ypos, void *param)
{
	t_data			*data;

	(void)ypos;
	data = (t_data *)param;
	if (data->input.skip_next_mouse_input)
	{
		data->input.skip_next_mouse_input = 0;
		return;
	}
	data->input.delta_mouse_x = (int)xpos - (data->mlx.win_size.x >> 1);
	data->input.mouse_input = 1;
}

static void	handle_mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_data			*data;

	(void)button;
	(void)action;
	(void)mods;
	data = (t_data *)param;
	if (data->input.skip_next_mouse_input)
	{
		data->input.skip_next_mouse_input = 0;
		return;
	}
	data->input.delta_mouse_x = data->mlx.mouse_x - (data->mlx.win_size.x >> 1);
	data->input.mouse_input = 1;
}

#if ENABLE_MULTI_THREAD_RENDERING == 1

void	cub_loop(t_data *data)
{
	mlx_close_hook(data->mlx.mlx_ptr, &handle_close, data);
	mlx_key_hook(data->mlx.mlx_ptr, &handle_key, data);
	mlx_key_hook(data->mlx.mlx_ptr, &handle_key_release, &data->input);
	mlx_cursor_hook(data->mlx.mlx_ptr, &handle_mouse, data);
	mlx_mouse_hook(data->mlx.mlx_ptr, &handle_mouse_press, data);
	if (cub_render_pool_init(&data->pool) != 0)
	{
		handle_close(data);
		return;
	}
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_image_to_window(data->mlx.mlx_ptr, data->mlx.backbuffer.img, 0, 0);
	mlx_loop_hook(data->mlx.mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx.mlx_ptr);
}

#else

void	cub_loop(t_data *data)
{
	mlx_close_hook(data->mlx.mlx_ptr, &handle_close, data);
	mlx_key_hook(data->mlx.mlx_ptr, &handle_key, data);
	mlx_key_hook(data->mlx.mlx_ptr, &handle_key_release, &data->input);
	mlx_cursor_hook(data->mlx.mlx_ptr, &handle_mouse, data);
	mlx_mouse_hook(data->mlx.mlx_ptr, &handle_mouse_press, data);
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_image_to_window(data->mlx.mlx_ptr, data->mlx.backbuffer.img, 0, 0);
	mlx_loop_hook(data->mlx.mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx.mlx_ptr);
}

#endif
