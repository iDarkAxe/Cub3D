/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:12:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/20 10:01:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "so_long.h"

ssize_t	ft_print_position(int x, int y)
{
	ssize_t	count_printed;

	count_printed = 0;
	count_printed += write(1, "Pos: x,y(", 9);
	count_printed += ft_putnbr_fd(x, 1);
	count_printed += write(1, ", ", 2);
	count_printed += ft_putnbr_fd(y, 1);
	count_printed += write(1, ")\n", 2);
	return (count_printed);
}

ssize_t	ft_print_color(int color)
{
	ssize_t	count_printed;

	count_printed = 0;
	count_printed += write(1, "Color: ", 7);
	count_printed += ft_putnbr_fd(color, 1);
	count_printed += write(1, "\n", 1);
	return (count_printed);
}

ssize_t	ft_print_keycode(int keycode)
{
	ssize_t	count_printed;

	count_printed = 0;
	count_printed += write(1, "Keycode: ", 9);
	count_printed += ft_putnbr_fd(keycode, 1);
	count_printed += write(1, "\n", 1);
	return (count_printed);
}

ssize_t	ft_print_map(t_map *map, char **map_to_print)
{
	ssize_t	count_printed;
	size_t	count;

	count_printed = 0;
	count = 0;
	while (count < map->height + 1)
	{
		count_printed += write(1, map_to_print[count], map->width);
		count_printed += write(1, "\n", 1);
		count++;
	}
	return (count_printed);
}

ssize_t	ft_print_number_of_moves(size_t number_of_moves)
{
	ssize_t	count_printed;

	count_printed = 0;
	count_printed += write(1, "Number of moves: ", 17);
	count_printed += ft_putnbr_fd((long long)number_of_moves, 1);
	count_printed += write(1, "\n", 1);
	return (count_printed);
}
