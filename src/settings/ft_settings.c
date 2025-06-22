/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 18:28:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_draw.h"
#include "ft_keys.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdio.h>

// TODO ERMOVE
#include <stdlib.h>

int				settings_handle_mouse_click(int button, int x, int y,
					void *param);
int				settings_close_window(void *param);
int				settings_handle_mouse_motion(int x, int y, void *param);
int				settings_handle_keypress(int keycode, void *param);

t_coordinates	ft_get_screen_size(void *mlx_ptr, int *x, int *y)
{
	if (!mlx_ptr || !x || !y)
		return ((t_coordinates){.x = 0, .y = 0});
	mlx_get_screen_size(mlx_ptr, x, y);
	return ((t_coordinates){.x = *x, .y = *y});
}

int	circle_state(int x, int y)
{
	if (x > 15 && x < 55)
	{
		if (y > 120 && y < 160)
			return (1);
		else if (y > 190 && y < 230)
			return (2);
		else if (y > 260 && y < 300)
			return (3);
		else if (y > 340 && y < 380)
			return (4);
	}
	return (0);
}

int	settings_loop_hook(void *param)
{
	static int	state_prev = 0;
	static int	state_actual = 0;
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (mlx->win_size.x != 0 || mlx->win_size.y != 0)
	{
		mlx_loop_hook(mlx->mlx_ptr, NULL, NULL);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_settings_ptr);
	}
	state_actual = circle_state(mlx->mouse_x, mlx->mouse_y);
	if (state_actual == state_prev || state_actual == 0)
		return (0);
	ft_draw_all_circle(mlx->mlx_ptr, mlx->win_settings_ptr, 0);
	ft_draw_all_circle(mlx->mlx_ptr, mlx->win_settings_ptr, state_actual);
	state_prev = state_actual;
	return (0);
}

void	settings_hooks(t_mlx *mlx)
{
	if (!mlx)
		return ;
	mlx_hook(mlx->win_settings_ptr, MotionNotify, PointerMotionMask,
		settings_handle_mouse_motion, mlx);
	mlx_hook(mlx->win_settings_ptr, KeyPress, KeyPressMask,
		settings_handle_keypress, NULL);
	mlx_hook(mlx->win_settings_ptr, 17, 0, settings_close_window, mlx);
	mlx_hook(mlx->win_settings_ptr, ButtonPress, ButtonPressMask,
		settings_handle_mouse_click, mlx);
	ft_draw_all_circle(mlx->mlx_ptr, mlx->win_settings_ptr, 0);
	mlx_loop_hook(mlx->mlx_ptr, settings_loop_hook, mlx);
}

void	*ft_settings(t_mlx *mlx)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "img/settings.xpm",
			&img.width, &img.width);
	if (img.ptr == NULL)
	{
		free(mlx->mlx_ptr);
		return (NULL);
	}
	mlx->win_settings_ptr = mlx_new_window(mlx->mlx_ptr, 500, 500, "Settings");
	if (mlx->win_settings_ptr == NULL)
	{
		free(mlx->mlx_ptr);
		return (NULL);
	}
	mlx->mouse_x = -1;
	mlx->mouse_y = -1;
	mlx->win_size = (t_coordinates){0, 0};
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_settings_ptr, img.ptr, 0, 0);
	settings_hooks(mlx);
	return (mlx->win_settings_ptr);
}
