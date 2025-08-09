/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/07 19:10:51 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "mlx.h"
#include "cub3d.h"

void	state_machine(int keycode, t_mlx *mlx)
{
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
}

enum e_screen_size	circle_state(int x, int y)
{
	if (x > 15 && x < 55)
	{
		if (y > 60 && y < 100)
			return (SIZE_FULL_SCREEN);
		if (y > 120 && y < 160)
			return (SIZE_4K);
		else if (y > 190 && y < 230)
			return (SIZE_2K);
		else if (y > 260 && y < 300)
			return (SIZE_1080P);
		else if (y > 340 && y < 380)
			return (SIZE_720P);
		else if (y > 420 && y < 460)
			return (SIZE_480P);
	}
	return (SIZE_NONE);
}
