/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:51:57 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/21 12:54:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

// /**
//  * @brief DFS pour valider l'accessibilité des collectibles et de la sortie.
//  *
//  * @param map Structure contenant la carte.
//  * @param pos Position actuelle (x, y) dans la carte.
//  * @return int 1 si toutes les pièces sont accessibles, 0 sinon.
//  */

static int	is_all_accessible(t_map *map, char **new_map);
static int	is_wall(size_t x, size_t y, char **map);
static void	pathing(t_map *map, size_t x, size_t y, char **new_map);

int	validate_map(t_map *map)
{
	char	**new_map;
	size_t	i;
	int		ret;

	i = 0;
	new_map = malloc(sizeof(char *) * (map->height + 1));
	if (new_map == NULL)
		return (-1);
	while (i <= map->height)
	{
		new_map[i] = ft_strdup(map->map[i]);
		if (new_map[i] == NULL)
			return ((void)free(new_map), -1);
		i++;
	}
	ret = is_all_accessible(map, new_map);
	while (i > 0)
		free(new_map[i-- - 1]);
	free(new_map);
	if (ret == 1)
		return (-1);
	return (0);
}

/**
 * @brief Check if the position is a wall.
 * Transforms all the letters seen into its lowercase version.
 * 
 * @param x Position x.
 * @param y Position y.
 * @param map Map to check (Array of strings).
 * @return int 1 if not a wall, 0 if a wall.
 */
static int	is_wall(size_t x, size_t y, char **map)
{
	if (map[y][x] >= 'A' && map[y][x] <= 'Z')
	{
		map[y][x] = map[y][x] + 32;
		return (1);
	}
	if (map[y][x] == '0')
	{
		map[y][x] = '2';
		return (1);
	}
	return (0);
}

/**
 * @brief Pathing function for the DFS. (Depth First Search)
 * Uses recursion to visit all the tiles from player position.
 * 
 * @param map Structure containing the map.
 * @param x Position x.
 * @param y Position y.
 * @param new_map Map to check (Array of strings).
 */
static void	pathing(t_map *map, size_t x, size_t y, char **new_map)
{
	if (is_wall(x + 1, y, new_map))
		pathing(map, x + 1, y, new_map);
	if (is_wall(x - 1, y, new_map))
		pathing(map, x - 1, y, new_map);
	if (is_wall(x, y + 1, new_map))
		pathing(map, x, y + 1, new_map);
	if (is_wall(x, y - 1, new_map))
		pathing(map, x, y - 1, new_map);
}

/**
 * @brief Verify if all the collectibles and the exit are accessible.
 * If a floor is not accessible, it will not warn an error.
 * 
 * @param map Structure containing the map.
 * @param new_map Map to check (Array of strings).
 * @return int -1 if not accessible, 0 if all collectibles or exit atteigned
 */
static int	is_all_accessible(t_map *map, char **new_map)
{
	t_coordinates	map_pos;
	t_coordinates	player_pos;

	map_pos.y = 0;
	player_pos = find_position(map, 'P');
	pathing(map, player_pos.x, player_pos.y, new_map);
	while (map_pos.y < map->height && new_map[map_pos.y])
	{
		map_pos.x = 0;
		while (map_pos.y < map->height && map_pos.x < map->width
			&& new_map[map_pos.y][map_pos.x])
		{
			if (new_map[map_pos.y][map_pos.x] == 'E'
				|| new_map[map_pos.y][map_pos.x] == 'C')
				return (1);
			map_pos.x++;
		}
		map_pos.y++;
	}
	return (0);
}
