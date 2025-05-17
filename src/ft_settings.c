/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:55:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/16 11:45:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_settings.c

 * @brief Functions related to the settings window.
 * @deprecated This file is deprecated.
 */

#include "keys.h"
#include "mlx.h"
#include "so_long.h"
#include <stddef.h>
#include <unistd.h>
#include "ft_print.h"

#include <stdlib.h>

int	handle_mouse_motion_settings(int x, int y, void *param);

/**
 * @brief Draw the circle on the setting window.
 * 
 * @param mlx_ptr mlx instance pointer.
 * @param win_settings_ptr window instance pointer.
 */
static void	ft_draw_all_circle(void *mlx_ptr, void *win_settings_ptr)
{
	ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 140, 20,
		0xFFAA00});
	ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 210, 20,
		0xFFAA00});
	ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 280, 20,
		0xFFAA00});
	ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 360, 20,
		0xFFAA00});
}

int	handle_mouse_motion_settings(int x, int y, void *param)
{
	ft_print_position(x, y);
	if (x > 15 && x < 55 && y > 120 && y < 160)
		ft_draw_circle(((t_mlx *)param)->mlx_ptr,
			((t_mlx *)param)->win_settings_ptr, (t_circle){35, 140, 20,
			0x00FF00});
	else if (x > 15 && x < 55 && y > 190 && y < 230)
		ft_draw_circle(((t_mlx *)param)->mlx_ptr,
			((t_mlx *)param)->win_settings_ptr, (t_circle){35, 210, 20,
			0x00FF00});
	else if (x > 15 && x < 55 && y > 260 && y < 300)
		ft_draw_circle(((t_mlx *)param)->mlx_ptr,
			((t_mlx *)param)->win_settings_ptr, (t_circle){35, 280, 20,
			0x00FF00});
	else if (x > 15 && x < 55 && y > 340 && y < 380)
		ft_draw_circle(((t_mlx *)param)->mlx_ptr,
			((t_mlx *)param)->win_settings_ptr, (t_circle){35, 360, 20,
			0x00FF00});
	else
	{
		ft_draw_all_circle(((t_mlx *)param)->mlx_ptr,
			((t_mlx *)param)->win_settings_ptr);
	}
	return (0);
}

static int	handle_keypress_settings(int keycode, void *param)
{
	(void)param;
	ft_print_keycode(keycode);
	if (keycode == KEY_ESCAPE)
		exit(0);
	return (keycode);
}

void	*ft_settings(t_mlx *mlx)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "img/settings.xpm",
			&img.width, &img.width);
	mlx->win_settings_ptr = mlx_new_window(mlx->mlx_ptr, 500, 500, "Settings");
	if (mlx->win_settings_ptr == NULL)
	{
		free(mlx->mlx_ptr);
		return (NULL);
	}
	if (img.ptr == NULL)
	{
		free(mlx->mlx_ptr);
		return (NULL);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_settings_ptr, img.ptr, 0, 0);
	ft_draw_all_circle(mlx->mlx_ptr, mlx->win_settings_ptr);
	mlx_hook(mlx->win_settings_ptr, MotionNotify, PointerMotionMask,
		handle_mouse_motion_settings, mlx);
	mlx_hook(mlx->win_settings_ptr, KeyPress, KeyPressMask,
		handle_keypress_settings, NULL);
	mlx_hook(mlx->win_settings_ptr, 17, 0, close_window, NULL);
	return (mlx->win_settings_ptr);
}

// static int	ft_screen_size(void *mlx_ptr)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	mlx_get_screen_size(mlx_ptr, &x, &y);
// 	mlx_new_window(mlx_ptr, x, y, "So_long");
// 	return (0);
// }
