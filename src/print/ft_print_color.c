/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:12:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 15:00:18 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

void	ft_print_color(t_color *color)
{
	printf("r:%3d g:%3d b:%3d, rgba:#%02x%02x%02x%02x\n", color->red,
		color->green, color->blue, color->red,
		color->green, color->blue, color->alpha);
}

void	ft_print_floor_ceiling(t_map *map)
{
	if (map == NULL || map->map_2d == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap or map->map_2d is NULL\n");
		return ;
	}
	printf("Floor:\n");
	ft_print_color(&map->textures.floor);
	printf("Ceiling:\n");
	ft_print_color(&map->textures.ceiling);
}
