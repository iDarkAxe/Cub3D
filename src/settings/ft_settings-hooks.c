/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings-hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/26 11:56:30 by ppontet          ###   ########lyon.fr   */
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
	mlx_get_screen_size(mlx->mlx_ptr, (int *)&mlx->win_size.x,
		(int *)&mlx->win_size.y);
	return (0);
}

int	hook_settings_handle_keypress(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_printf("Key: %d\n", keycode);
	if (keycode == KEY_DOWN && mlx->settings_state == SIZE_1080P)
		mlx->settings_state = SIZE_FULL_SCREEN;
	else if (keycode == KEY_UP && mlx->settings_state == SIZE_FULL_SCREEN)
		mlx->settings_state = SIZE_1080P;
	else if (keycode == KEY_DOWN && mlx->settings_state < SIZE_1080P)
		mlx->settings_state++;
	else if (keycode == KEY_UP && mlx->settings_state > SIZE_FULL_SCREEN)
		mlx->settings_state--;
	else if (keycode == KEY_ESCAPE && mlx->settings_state == 0)
		return (ft_set_screen_size(mlx, 1));
	else if ((keycode == KEY_ESCAPE || keycode == KEY_ENTER)
		&& mlx->settings_state != 0)
		return (ft_set_screen_size(mlx, mlx->settings_state));
	return (keycode);
}

int	hook_settings_handle_mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	(void)x;
	(void)y;
	if (button == 1)
		return (ft_set_screen_size(mlx, mlx->settings_state));
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
		mlx->settings_state = state;
	return (0);
}
