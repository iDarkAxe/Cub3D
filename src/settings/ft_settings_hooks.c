/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:06:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/08 16:19:01 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_keys.h"
#include "ft_print.h"
#include "MLX42/MLX42.h"

void	hook_settings_close_window(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (CROSS_APPLY_SETTINGS)
		ft_set_screen_size(mlx, mlx->settings.state);
	else
		mlx_close_window(mlx->settings.win_ptr);
}

void	hook_settings_handle_keypress(keys_t key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (DEBUG_PRINT_KEYCODE == 1)
		ft_print_key((int)key);
	if (key == MLX_KEY_ESCAPE && ESCAPE_APPLY_SETTINGS == 0)
		mlx_close_window(mlx->settings.win_ptr);
	else
		state_machine((int)key, mlx);
}

void	hook_settings_handle_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	(void)action;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
		ft_set_screen_size(mlx, mlx->settings.state);
}

void	hook_settings_handle_mouse_motion(double xpos, double ypos, void *param)
{
	t_mlx				*mlx;
	enum e_screen_size	state;

	mlx = (t_mlx *)param;
	mlx->mouse_x = (int)xpos;
	mlx->mouse_y = (int)ypos;
	state = circle_state((int)xpos, (int)ypos);
	if (state != 0)
		mlx->settings.state = state;
}
