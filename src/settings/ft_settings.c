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
#include "MLX42.h"
#include <stdlib.h>

static void	settings_loop_hook(void *param);
static void	settings_changed(t_data *data);

void	*ft_settings(t_mlx *mlx)
{
	mlx_texture_t	*texture;

	texture = mlx_load_xpm42(mlx->mlx_ptr, "img/settings.xpm");
	if (texture == NULL)
		return (NULL);
	mlx->settings.background.img = mlx_texture_to_image(mlx->mlx_ptr, texture);
	if (mlx->settings.background.img == NULL)
		return (NULL);
	mlx->settings.background.width = mlx->settings.background.img->width;
	mlx->settings.background.height = mlx->settings.background.img->height;
	mlx->settings.win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->settings.background.width, mlx->settings.background.height,
			"Settings");
	if (mlx->settings.win_ptr == NULL)
		return (NULL);
	mlx_image_to_window(mlx->mlx_ptr, mlx->settings.background.img, 0, 0);
	mlx_delete_image(mlx->mlx_ptr, mlx->settings.background.img);
	mlx->settings.background.img = NULL;

	mlx->settings.circle_no.img = mlx_load_xpm42(mlx->mlx_ptr,
			"img/circle-unselected.xpm");
	if (mlx->settings.circle_no.img == NULL)
		return (NULL);
	mlx->settings.circle_no.img = mlx_texture_to_image(mlx->mlx_ptr,
			mlx->settings.circle_no.img);
	if (mlx->settings.circle_no.img == NULL)
		return (NULL);

	mlx->settings.circle_yes.img = mlx_load_xpm42(mlx->mlx_ptr,
			"img/circle-selected.xpm");
	if (mlx->settings.circle_yes.img == NULL)
		return (NULL);
	mlx->settings.circle_yes.img = mlx_texture_to_image(mlx->mlx_ptr,
			mlx->settings.circle_yes.img);
	if (mlx->settings.circle_yes.img == NULL)
		return (NULL);

	ft_put_all_circle_to_win(mlx, mlx->settings.win_ptr, 0);
	ft_put_circle_specific(mlx, mlx->settings.win_ptr, mlx->settings.state, 1);
	return (mlx->settings.win_ptr);
}

void	settings_hooks(t_data *data)
{
	if (!data)
		return;
	mlx_cursor_hook(data->mlx.settings.win_ptr, (mlx_cursorfunc)hook_settings_handle_mouse_motion, &data->mlx);
	mlx_key_hook(data->mlx.settings.win_ptr, (mlx_keyfunc)hook_settings_handle_keypress, &data->mlx);
	mlx_close_hook(data->mlx.settings.win_ptr, (mlx_closefunc)hook_settings_close_window, &data->mlx);
	mlx_mouse_hook(data->mlx.settings.win_ptr, (mlx_mousefunc)hook_settings_handle_mouse_click, &data->mlx);
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
	if (data->mlx.win_ptr != NULL)
		mlx_delete_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			data->mlx.win_size.x, data->mlx.win_size.y, "Cub3D");
	if (data->mlx.win_ptr == NULL)
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

		mlx_get_screen_size(mlx->mlx_ptr, &width, &height);
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
