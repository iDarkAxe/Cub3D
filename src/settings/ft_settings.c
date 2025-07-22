/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/22 16:10:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "ft_draw.h"
#include "ft_keys.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

static int			settings_loop_hook(void *param);
static void			settings_hooks(t_mlx *mlx);
int					cub3d_rendu(t_mlx *mlx);

void	*ft_settings(t_mlx *mlx)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx->mlx_ptr, "img/settings.xpm",
			&img.width, &img.width);
	if (img.img == NULL)
	{
		free(mlx->mlx_ptr);
		return (NULL);
	}
	mlx->settings.win_ptr = mlx_new_window(mlx->mlx_ptr, 500, 500, "Settings");
	if (mlx->settings.win_ptr == NULL)
	{
		free(mlx->mlx_ptr);
		return (NULL);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->settings.win_ptr, img.img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, img.img);
	mlx->settings.circle_no.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"img/circle-unselected.xpm", &img.width, &img.width);
	mlx->settings.circle_yes.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"img/circle-selected.xpm", &img.width, &img.width);
	ft_put_all_circle_to_win(mlx, mlx->settings.win_ptr, 0);
	ft_put_circle_specific(mlx, mlx->settings.win_ptr, mlx->settings.state, 1);
	settings_hooks(mlx);
	return (mlx->settings.win_ptr);
}

void	settings_hooks(t_mlx *mlx)
{
	if (!mlx)
		return ;
	mlx_hook(mlx->settings.win_ptr, MotionNotify, PointerMotionMask,
		hook_settings_handle_mouse_motion, mlx);
	mlx_hook(mlx->settings.win_ptr, KeyPress, KeyPressMask,
		hook_settings_handle_keypress, mlx);
	mlx_hook(mlx->settings.win_ptr, 17, 0, hook_settings_close_window, mlx);
	mlx_hook(mlx->settings.win_ptr, ButtonPress, ButtonPressMask,
		hook_settings_handle_mouse_click, mlx);
	mlx_loop_hook(mlx->mlx_ptr, settings_loop_hook, mlx);
}

int	settings_loop_hook(void *param)
{
	static enum e_screen_size	state_prev = SIZE_FULL_SCREEN;
	static enum e_screen_size	state_actual = SIZE_FULL_SCREEN;
	t_mlx						*mlx;

	mlx = (t_mlx *)param;
	if (mlx->win_size.x != 0 || mlx->win_size.y != 0)
	{
		mlx_loop_hook(mlx->mlx_ptr, NULL, NULL);
		mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, (int)mlx->win_size.x,
				(int)mlx->win_size.y, "Cub3d");
		if (mlx->win_ptr == NULL)
			return (-1);
		ft_free_settings(mlx);
		main_hooks(mlx);
		cub3d_rendu(mlx);
	}
	state_actual = mlx->settings.state;
	if (state_actual == state_prev || state_actual == 0)
		return (0);
	ft_put_circle_specific(mlx, mlx->settings.win_ptr, state_prev, 0);
	ft_put_circle_specific(mlx, mlx->settings.win_ptr, state_actual, 1);
	state_prev = state_actual;
	return (0);
}

int	ft_set_screen_size(t_mlx *mlx, enum e_screen_size size)
{
	if (size == SIZE_FULL_SCREEN)
		mlx_get_screen_size(mlx->mlx_ptr, (int *)&mlx->win_size.x,
			(int *)&mlx->win_size.y);
	else if (size == SIZE_4K)
		mlx->win_size = (t_coordinates){3840, 2160};
	else if (size == SIZE_2K)
		mlx->win_size = (t_coordinates){2560, 1440};
	else if (size == SIZE_1080P)
		mlx->win_size = (t_coordinates){1920, 1080};
	else if (size == SIZE_720P)
		mlx->win_size = (t_coordinates){1280, 720};
	else if (size == SIZE_480P)
		mlx->win_size = (t_coordinates){640, 480};
	else
		return (-1);
	return (0);
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
