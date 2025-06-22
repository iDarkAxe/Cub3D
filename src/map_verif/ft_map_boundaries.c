/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_boundaries.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:15:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 12:38:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>
#include "libft.h"

t_coordinates	find_position(t_map *map, const char *charset);

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_in_bounds(char **map, size_t y, size_t x)
{
	if (!map || y >= count_array_length(map))
		return (0);
	if (x >= ft_strlen(map[y]))
		return (0);
	return (1);
}

t_coordinates	find_position(t_map *map, const char *charset)
{
	t_coordinates	pos;
	size_t			height;

	height = count_array_length(map->map);
	pos.y = 0;
	while (pos.y < height && map->map[pos.y])
	{
		pos.x = 0;
		while (map->map[pos.y][pos.x])
		{
			if (ft_strchr(charset, map->map[pos.y][pos.x]))
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return ((t_coordinates){.x = (size_t)-1, .y = (size_t)-1});
}
