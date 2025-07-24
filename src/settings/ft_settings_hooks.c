/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/24 11:59:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "mlx.h"
#include <X11/X.h>

int	hook_settings_close_window(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (CROSS_APPLY_SETTINGS)
		ft_set_screen_size(mlx, mlx->settings.state);
	else
		mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

/**
 * @brief Handle mouse click in the settings window.
 * SIZE_480P is the lowest in the list and SIZE_FULL_SCREEN is the highest.
 * 
 * @param keycode keycode of the key pressed
 * @param param Pointer to the mlx structure
 * @return int 
 */
int	hook_settings_handle_keypress(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_print_key(keycode);
	if (keycode == KEY_ESCAPE && ESCAPE_APPLY_SETTINGS == 0)
	{
		mlx_loop_end(mlx->mlx_ptr);
		return (keycode);
	}
	if (keycode == KEY_ESCAPE && mlx->settings.state == 0)
		ft_set_screen_size(mlx, SIZE_FULL_SCREEN);
	else if ((keycode == KEY_ESCAPE || keycode == KEY_ENTER
			|| keycode == KEY_SPACE) && mlx->settings.state != 0)
		ft_set_screen_size(mlx, mlx->settings.state);
	else if (is_mv_key(MV_DOWN, keycode) && mlx->settings.state == SIZE_480P)
		mlx->settings.state = SIZE_FULL_SCREEN;
	else if (is_mv_key(MV_UP, keycode)
		&& mlx->settings.state == SIZE_FULL_SCREEN)
		mlx->settings.state = SIZE_480P;
	else if (is_mv_key(MV_DOWN, keycode) && mlx->settings.state < SIZE_480P)
		mlx->settings.state++;
	else if (is_mv_key(MV_UP, keycode)
		&& mlx->settings.state > SIZE_FULL_SCREEN)
		mlx->settings.state--;
	return (keycode);
}

int	hook_settings_handle_mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	(void)x;
	(void)y;
	if (button == 1)
		return (ft_set_screen_size(mlx, mlx->settings.state));
	return (0);
}

int	hook_settings_handle_mouse_motion(int x, int y, void *param)
{
	t_mlx				*mlx;
	enum e_screen_size	state;

	mlx = (t_mlx *)param;
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	state = circle_state(x, y);
	if (state != 0)
		mlx->settings.state = state;
	return (0);
}
