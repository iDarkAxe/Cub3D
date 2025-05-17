/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:46:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 11:35:33 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include "mlx.h"

// TODO Etudier pertinence

int	find_max_collectibles(t_map *map)
{
	int		collectibles;
	size_t	x;
	size_t	y;

	collectibles = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'C')
				collectibles++;
			x++;
		}
		y++;
	}
	return (collectibles);
}

t_coordinates	find_position(t_map *map, char character)
{
	t_coordinates	player;

	player.y = 0;
	while (player.y < map->height && map->map[player.y] != NULL)
	{
		player.x = 0;
		while (player.x < map->width && map->map[player.y][player.x] != '\0')
		{
			if (map->map[player.y][player.x] == character)
				break ;
			player.x++;
		}
		if (map->map[player.y][player.x] == character)
			break ;
		player.y++;
	}
	return (player);
}
