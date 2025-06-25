/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:16:53 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 09:17:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_printf.h"
#include "mlx.h"
#include <X11/X.h>

void	main_hooks(t_mlx *mlx);
int		hook_handle_mouse_motion(int x, int y, void *param);
int		hook_close_window(void *param);
int		hook_handle_keypress(int keycode, void *param);

void	main_hooks(t_mlx *mlx)
{
	if (!mlx)
		return ;
	mlx_hook(mlx->win_ptr, MotionNotify, PointerMotionMask,
		hook_handle_mouse_motion, mlx);
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, hook_handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, hook_close_window, mlx);
}

int	hook_handle_mouse_motion(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	return (0);
}

int	hook_close_window(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	hook_handle_keypress(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_printf("Key: %d\n", keycode);
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(mlx->mlx_ptr);
	if (keycode != KEY_ENTER)
		return (0);
	return (keycode);
}
