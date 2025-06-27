/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:04:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/26 14:11:31 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_keys.h"
#include <stdbool.h>

bool	is_mv_key(enum e_movement expected, int keycode)
{
	if (expected == MV_UP && ((keycode) == KEY_ARROW_UP || (keycode) == KEY_W))
		return (true);
	if (expected == MV_LEFT && ((keycode) == KEY_ARROW_LEFT
			|| (keycode) == KEY_A))
		return (true);
	if (expected == MV_RIGHT && ((keycode) == KEY_ARROW_RIGHT
			|| (keycode) == KEY_D))
		return (true);
	if (expected == MV_DOWN && ((keycode) == KEY_ARROW_DOWN
			|| (keycode) == KEY_S))
		return (true);
	return (false);
}
