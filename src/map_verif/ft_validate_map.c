/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:45:32 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 15:00:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "libft.h"
#include <stdlib.h>

static int	is_leaking(char **map, size_t y, size_t x, char **visited)
{
	if (!is_in_bounds(map, y, x) || map[y][x] == ' ')
	{
		print_leak_map(map, y, x);
		return (1);
	}
	if (visited[y][x] || map[y][x] == '1')
		return (0);
	visited[y][x] = 1;
	if (is_leaking(map, y + 1, x, visited) || is_leaking(map, y - 1, x, visited)
		|| is_leaking(map, y, x + 1, visited) || is_leaking(map, y, x - 1,
			visited))
		return (1);
	return (0);
}

static char	**alloc_visited(char **map)
{
	size_t	height;
	char	**visited;
	size_t	i;

	height = count_array_length(map);
	visited = malloc(sizeof(char *) * (height + 1));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(char));
		if (!visited[i])
		{
			ft_frees((void **)visited);
			return (NULL);
		}
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

int	validate_map(t_map *map)
{
	t_coordinates	pos;
	char			**visited;

	pos = find_position(map, "NSWE");
	if (!is_in_bounds(map->map_2d, pos.y, pos.x))
		return (-1);
	visited = alloc_visited(map->map_2d);
	if (!visited)
		return (-1);
	if (is_leaking(map->map_2d, pos.y, pos.x, visited))
	{
		ft_frees((void **)visited);
		return (-1);
	}
	ft_frees((void **)visited);
	return (0);
}
