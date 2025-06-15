/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:12:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/15 13:18:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include "cub3d.h"
#include <stdio.h>

ssize_t	ft_print_position(int x, int y)
{
	return (ft_printf("Pos: x,y(%d, %d)\n", x, y));
}

ssize_t	ft_print_map(t_map *map, char **map_to_print)
{
	ssize_t	count_printed;
	ssize_t	temp;
	size_t	count;

	if (map == NULL || map_to_print == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap or map_to_print is NULL\n");
		return (-1);
	}
	count_printed = 0;
	count = 0;
	while (count < map->file_nb_lines + 1 && map_to_print[count] != NULL)
	{
		temp = ft_printf("%s", map_to_print[count]);
		if (temp < 0)
			return (temp);
		count_printed += temp;
		count++;
	}
	temp = ft_printf("\n");
	if (temp < 0)
		return (temp);
	count_printed += temp;
	return (count_printed);
}

ssize_t	ft_print_number_of_moves(size_t number_of_moves)
{
	return (printf("Number of moves: %zu\n", number_of_moves));
}
