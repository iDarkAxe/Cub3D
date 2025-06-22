/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings-hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 18:20:07 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_print.h"
#include "mlx.h"
#include <X11/X.h>

// TODO ERMOVE
#include <stdio.h>
#include <stdlib.h>

t_coordinates	ft_get_screen_size(void *mlx_ptr, int *x, int *y);
int				circle_state(int x, int y);

int	settings_close_window(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_get_screen_size(mlx->mlx_ptr, (int *)&mlx->win_size.x,
		(int *)&mlx->win_size.y);
	return (0);
}

int	settings_handle_mouse_motion(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_print_position(x, y);
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	return (0);
}

int	settings_handle_keypress(int keycode, void *param)
{
	(void)param;
	printf("Key: %d\n", keycode);
	if (keycode == KEY_ESCAPE)
		exit(0);
	return (keycode);
}

int	settings_handle_mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	int		state;

	mlx = (t_mlx *)param;
	if (button == 1)
	{
		state = circle_state(x, y);
		if (state == 0)
			return (0);
		if (state == 1)
			ft_get_screen_size(mlx->mlx_ptr, (int *)&mlx->win_size.x,
				(int *)&mlx->win_size.y);
		if (state == 2)
			mlx->win_size = (t_coordinates){3840, 2160};
		if (state == 3)
			mlx->win_size = (t_coordinates){2560, 1440};
		if (state == 4)
			mlx->win_size = (t_coordinates){1920, 1080};
	}
	return (0);
}
