/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:45:04 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 12:26:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static int		check_map_verify_count(t_map *map);

/**
 * @brief Initialize the map structure.
 * It's used to set the map structure to NULL and 0.
 * It's used to avoid undefined behavior or double free.
 *
 * @param map Pointer to the map structure.
 * @param map_size Map dimensions and metadata.
 */
static void	map_init(t_map *map, t_map_size map_size)
{
	map->map = NULL;
	map->error = 0;
	map->width = map_size.line_len;
	map->height = map_size.count_line;
	map->number_of_moves = 0;
	map->collectibles = 0;
	map->exit = (t_coordinates){0, 0};
	map->textures.north.ptr = NULL;
	map->textures.east.ptr = NULL;
	map->textures.west.ptr = NULL;
	map->textures.south.ptr = NULL;
}

/**
 * @brief Store the map in the map structure.
 *
 *
 * @param map Pointer to the map structure.
 * @param map_size Map dimensions and metadata.
 * @return t_map* Map structure if success, NULL otherwise.
 */
static t_map	*store_map(t_map *map, t_map_size map_size)
{
	size_t	i;
	ssize_t	ret;

	map_size.fd = open(map_size.map_name, O_RDONLY);
	if (map_size.fd == -1)
		return (NULL);
	i = 0;
	ret = 1;
	while (i <= map->height && ret != 0)
	{
		ret = read(map_size.fd, map->map[i], map_size.line_len + 1);
		if (ret == -1)
			return ((void)free_map(map, map->map, i), NULL);
		map->map[i][ret] = '\0';
		i++;
	}
	close(map_size.fd);
	return (map);
}

t_map	*fill_map(t_map *map, t_map_size map_size)
{
	size_t	i;

	i = 0;
	if (map == NULL)
		return (NULL);
	map_init(map, map_size);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (map->map == NULL)
		return (NULL);
	while (i <= map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 2));
		if (map->map[i] == NULL)
			return ((void)free_map(map, map->map, i), NULL);
		i++;
	}
	if (store_map(map, map_size) == NULL || check_map_verify_count(map) == -1
		|| validate_map(map) == -1)
		return ((void)free_map(map, map->map, map->height), NULL);
	return (map);
}

/**
 * @brief Check if a character is valid.
 *
 * @param c character to check.
 * @return int 1
 */
static int	ft_is_char_valid(char c)
{
	if (c == 'C' || c == 'E' || c == 'P' || c == '0' || c == '1')
		return (1);
	return (0);
}

/**
 * @brief Check if the map has the correct number of collectibles,
 * player and exit.
 * Uses a rectangle to store the count of each character (P, E, C),
 * and checks if the count is correct.
 *
 * @param map Pointer to the map structure.
 * @return int 0 if the map is correct, -1 otherwise.
 */
static int	check_map_verify_count(t_map *map)
{
	t_coordinates	coords;
	t_rectangle		rect;

	coords.x = 0;
	rect = (t_rectangle){0, 0, 0, 0, 0};
	while (coords.x < map->height)
	{
		coords.y = 0;
		while (coords.y < map->width)
		{
			if (map->map[coords.x][coords.y] == 'P')
				rect.x++;
			if (map->map[coords.x][coords.y] == 'E')
				rect.y++;
			if (map->map[coords.x][coords.y] == 'C')
				rect.height++;
			if (ft_is_char_valid(map->map[coords.x][coords.y]) != 1)
				return (-1);
			coords.y++;
		}
		coords.x++;
	}
	if (rect.x > 1 || rect.y > 1 || rect.height == 0)
		return (-1);
	return (0);
}
