/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:45:36 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/26 14:00:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_keys.h"
#include "ft_printf.h"

void	ft_print_key(int keycode)
{
	if (keycode == KEY_ARROW_UP)
		ft_printf("Key: UP\n");
	else if (keycode == KEY_ARROW_DOWN)
		ft_printf("Key: DOWN\n");
	else if (keycode == KEY_ARROW_LEFT)
		ft_printf("Key: LEFT\n");
	else if (keycode == KEY_ARROW_RIGHT)
		ft_printf("Key: RIGHT\n");
	else if (keycode == KEY_ESCAPE)
		ft_printf("Key: ESCAPE\n");
	else if (keycode == KEY_ENTER)
		ft_printf("Key: ENTER\n");
	else if (keycode == KEY_SPACE)
		ft_printf("Key: SPACE\n");
	else if (keycode == KEY_S)
		ft_printf("Key: S\n");
	else if (keycode == KEY_A)
		ft_printf("Key: A\n");
	else if (keycode == KEY_D)
		ft_printf("Key: D\n");
	else if (keycode == KEY_W)
		ft_printf("Key: W\n");
	else
		ft_printf("Key: %d\n", keycode);
}
