/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:59:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/20 15:53:00 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_keys.h"
#include "so_long.h"
#include <unistd.h>

#include "mlx.h"
#include <stdlib.h>

int	close_window(void *param)
{
	write(1, "Closing current window.\n", 24);
	mlx_loop_end(((t_mlx *)param)->mlx_ptr);
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	ft_print_keycode(keycode);
	if (keycode == KEY_ESCAPE)
		close_window(((t_store *)param)->mlx);
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT)
	{
		can_player_move(((t_store *)param)->mlx, ((t_store *)param)->map,
			keycode);
		((t_store *)param)->map->number_of_moves++;
		ft_print_number_of_moves(((t_store *)param)->map->number_of_moves);
	}
	return (keycode);
}

// __attribute__((deprecated))
// static int	handle_mouse_motion(int x, int y, void *param)
// {
// 	(void)param;
// 	ft_print_position(x, y);
// 	return (0);
// }
