/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 16:44:01 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "data_structure.h"
#include "ft_draw.h"
#include "ft_keys.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

static int			settings_loop_hook(void *param);
static void			settings_changed(t_data *data);

void	*ft_settings(t_mlx *mlx)
{
	mlx->settings.background.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"img/settings.xpm", &mlx->settings.background.width,
			&mlx->settings.background.width);
	if (mlx->settings.background.img == NULL)
		return (NULL);
	mlx->settings.win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->settings.background.width, mlx->settings.background.width,
			"Settings");
	if (mlx->settings.win_ptr == NULL)
		return (NULL);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->settings.win_ptr,
		mlx->settings.background.img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->settings.background.img);
	mlx->settings.background.img = NULL;
	mlx->settings.circle_no.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"img/circle-unselected.xpm", &mlx->settings.background.width,
			&mlx->settings.background.width);
	mlx->settings.circle_yes.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"img/circle-selected.xpm", &mlx->settings.background.width,
			&mlx->settings.background.width);
	ft_put_all_circle_to_win(mlx, mlx->settings.win_ptr, 0);
	ft_put_circle_specific(mlx, mlx->settings.win_ptr, mlx->settings.state, 1);
	return (mlx->settings.win_ptr);
}

void	settings_hooks(t_data *data)
{
	if (!data)
		return ;
	mlx_hook(data->mlx.settings.win_ptr, MotionNotify, PointerMotionMask,
		hook_settings_handle_mouse_motion, &data->mlx);
	mlx_hook(data->mlx.settings.win_ptr, KeyPress, KeyPressMask,
		hook_settings_handle_keypress, &data->mlx);
	mlx_hook(data->mlx.settings.win_ptr, DestroyNotify, StructureNotifyMask,
		hook_settings_close_window, &data->mlx);
	mlx_hook(data->mlx.settings.win_ptr, ButtonPress, ButtonPressMask,
		hook_settings_handle_mouse_click, &data->mlx);
	mlx_loop_hook(data->mlx.mlx_ptr, settings_loop_hook, data);
}

int	settings_loop_hook(void *param)
{
	static enum e_screen_size	state_prev = SIZE_FULL_SCREEN;
	static enum e_screen_size	state_actual = SIZE_FULL_SCREEN;
	t_data						*data;

	data = (t_data *)param;
	if (data->mlx.win_size.x != 0 || data->mlx.win_size.y != 0)
		settings_changed(data);
	state_actual = data->mlx.settings.state;
	if (state_actual == state_prev || state_actual == 0)
		return (0);
	ft_put_circle_specific(&data->mlx, data->mlx.settings.win_ptr, state_prev,
		0);
	ft_put_circle_specific(&data->mlx, data->mlx.settings.win_ptr, state_actual,
		1);
	state_prev = state_actual;
	return (0);
}

static void	settings_changed(t_data *data)
{
	mlx_loop_hook(data->mlx.mlx_ptr, NULL, NULL);
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			data->mlx.win_size.x, (int)data->mlx.win_size.y, "Cub3D");
	if (data->mlx.win_ptr == NULL)
		mlx_loop_end(data->mlx.mlx_ptr);
	ft_free_settings(&data->mlx);
	main_hooks(&data->mlx);
	if (cub3d_init_render(data) != 0)
		mlx_loop_end(data->mlx.mlx_ptr);
}

int	ft_set_screen_size(t_mlx *mlx, enum e_screen_size size)
{
	if (size == SIZE_FULL_SCREEN)
		mlx_get_screen_size(mlx->mlx_ptr, (int *)&mlx->win_size.x,
			(int *)&mlx->win_size.y);
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
