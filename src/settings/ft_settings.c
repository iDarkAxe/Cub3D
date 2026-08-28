/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/08 16:18:48 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "data_structure.h"
#include "ft_draw.h"
#include <MLX42.h>
#include <stdlib.h>
#include <stdio.h>
static void	settings_loop_hook(void *param);
static void	settings_changed(t_data *data);

void	*ft_settings(t_mlx *mlx)
{
	mlx_texture_t	*text;

	text = mlx_load_png("img/settings.png");
	if (text == NULL)
		return (NULL);
	mlx->mlx_ptr = mlx_init(500, 500, "Cub3D", true);
	printf("Text is %p\n", mlx->mlx_ptr);
	return (mlx->mlx_ptr);
}

void	settings_hooks(t_data *data)
{
	if (!data)
		return;
	mlx_cursor_hook(data->mlx.settings.win_ptr, hook_settings_handle_mouse_motion, &data->mlx);
	mlx_key_hook(data->mlx.settings.win_ptr, hook_settings_handle_keypress, &data->mlx);
	mlx_close_hook(data->mlx.settings.win_ptr, hook_settings_close_window, &data->mlx);
	mlx_mouse_hook(data->mlx.settings.win_ptr, hook_settings_handle_mouse_click, &data->mlx);
	mlx_loop_hook(data->mlx.mlx_ptr, settings_loop_hook, data);
}

static void	settings_loop_hook(void *param)
{
	static enum e_screen_size	state_prev = SIZE_FULL_SCREEN;
	static enum e_screen_size	state_actual = SIZE_FULL_SCREEN;
	t_data						*data;

	data = (t_data *)param;
	if (data->mlx.win_size.x != 0 || data->mlx.win_size.y != 0)
		settings_changed(data);
	state_actual = data->mlx.settings.state;
	if (state_actual == state_prev || state_actual == 0)
		return;
	ft_put_circle_specific(&data->mlx, data->mlx.settings.win_ptr, state_prev,
		0);
	ft_put_circle_specific(&data->mlx, data->mlx.settings.win_ptr, state_actual,
		1);
	state_prev = state_actual;
}

static void	settings_changed(t_data *data)
{
	mlx_loop_hook(data->mlx.mlx_ptr, NULL, NULL);
	if (data->mlx.mlx_ptr != NULL)
	{
		mlx_close_window(data->mlx.mlx_ptr);
		mlx_terminate(data->mlx.mlx_ptr);
	}
	data->mlx.mlx_ptr = mlx_init(data->mlx.win_size.x, data->mlx.win_size.y, "Cub3D", true);
	if (data->mlx.mlx_ptr == NULL)
		mlx_close_window(data->mlx.settings.win_ptr);
	ft_free_settings(&data->mlx);
	if (cub3d_init_render(data) != 0)
		mlx_close_window(data->mlx.settings.win_ptr);
}

int	ft_set_screen_size(t_mlx *mlx, enum e_screen_size size)
{
	if (size == SIZE_FULL_SCREEN)
	{
		int	width;
		int	height;

		// mlx_get_monitor_size requires mlx to be initialized
		if (mlx->mlx_ptr != NULL)
			mlx_get_monitor_size(0, &width, &height);
		else
		{
			// Fallback to 1080p if mlx not initialized yet
			width = 1920;
			height = 1080;
		}
		mlx->win_size.x = width;
		mlx->win_size.y = height;
	}
	else if (size == SIZE_4K)
		mlx->win_size = (t_pos2){3840, 2160};
	else if (size == SIZE_2K)
		mlx->win_size = (t_pos2){2560, 1440};
	else if (size == SIZE_1080P)
		mlx->win_size = (t_pos2){1920, 1080};
	else if (size == SIZE_720P)
		mlx->win_size = (t_pos2){1280, 720};
	else if (size == SIZE_480P)
		mlx->win_size = (t_pos2){640, 480};
	else
		return (-1);
	return (0);
}
