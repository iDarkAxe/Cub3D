/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings-hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 10:09:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "mlx.h"
#include <X11/X.h>

enum e_screen_size	circle_state(int x, int y);
int					ft_set_screen_size(t_mlx *mlx, enum e_screen_size size);

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
	if (keycode == KEY_ESCAPE && mlx->settings_state == 0)
		return (ft_set_screen_size(mlx, 1));
	if ((keycode == KEY_ESCAPE || keycode == KEY_ENTER)
		&& mlx->settings_state != 0)
		return (ft_set_screen_size(mlx, mlx->settings_state));
	return (keycode);
}

int	hook_settings_handle_mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (button == 1)
		return (ft_set_screen_size(mlx, circle_state(x, y)));
	return (0);
}
