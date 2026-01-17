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
#include "mlx.h"
#include <X11/X.h>

#if SKIP_NO_MVMT == 1

static int	loop_hook(void *param)
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
	mlx_mouse_move(data->mlx.mlx_ptr, data->mlx.win_ptr,
		half_win_size.x, half_win_size.y);
	cub_player_update(data);
	if (data->input.needs_render == false)
		return (1);
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.backbuffer.img, 0, 0);
	data->input.needs_render = false;
	return (1);
}

#else

static int	loop_hook(void *param)
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
	mlx_mouse_move(data->mlx.mlx_ptr, data->mlx.win_ptr,
		half_win_size.x, half_win_size.y);
	cub_player_update(data);
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.backbuffer.img, 0, 0);
	return (1);
}
#endif

#if ENABLE_MULTI_THREAD_RENDERING == 1

void	cub_loop(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask,
		&mlx_loop_end, data->mlx.mlx_ptr);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, &cub_keydown_hook,
		data);
	mlx_hook(data->mlx.win_ptr, KeyRelease, KeyReleaseMask, &cub_keyup_hook,
		&data->input);
	mlx_hook(data->mlx.win_ptr, MotionNotify, PointerMotionMask,
		&cub_mouse_hook, data);
	mlx_hook(data->mlx.win_ptr, ButtonPress, ButtonPressMask,
		&cub_mouse_click_hook, data);
	if (cub_render_pool_init(&data->pool) != 0)
	{
		mlx_loop_end(data->mlx.mlx_ptr);
		return ;
	}
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.backbuffer.img, 0, 0);
	mlx_loop_hook(data->mlx.mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx.mlx_ptr);
}

#else

void	cub_loop(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask,
		&mlx_loop_end, data->mlx.mlx_ptr);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, &cub_keydown_hook,
		data);
	mlx_hook(data->mlx.win_ptr, KeyRelease, KeyReleaseMask, &cub_keyup_hook,
		&data->input);
	mlx_hook(data->mlx.win_ptr, MotionNotify, PointerMotionMask,
		&cub_mouse_hook, data);
	mlx_hook(data->mlx.win_ptr, ButtonPress, ButtonPressMask,
		&cub_mouse_click_hook, data);
	cub_render(data);
	if (data->input.minimap)
		cub_render_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.backbuffer.img, 0, 0);
	mlx_loop_hook(data->mlx.mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx.mlx_ptr);
}

#endif
