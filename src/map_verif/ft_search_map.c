/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/11 18:39:51 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"
#include "ft_print.h"
#include <stdlib.h>

static size_t	count_map_size(t_map *map);
static int		validate_file_structure(t_map *map);
static int		validate_map_continuity(t_map *map);

size_t	count_map_size(t_map *map)
{
	size_t	index;
	size_t	count;

	if (!map || !map->file)
		return (0);
	index = 0;
	count = 0;
	while (map->file[index])
	{
		if (is_only_whitespace(map->file[index]) == false)
			count++;
		index++;
	}
	return (count);
}

char	**fill_map_region(t_map *map)
{
	size_t		index;
	uint32_t	nb_lines;

	if (!map || !map->file)
		return (NULL);
	if (validate_file_structure(map) != 0 || map->error != 0)
		return (NULL);
	map->map_2d = malloc(sizeof(char *) * (count_map_size(map) - 6 + 1));
	if (!map->map_2d)
		return (NULL);
	nb_lines = 0;
	index = 0;
	while (map->file[index] && (is_config_line(map->file[index])
			|| is_only_whitespace(map->file[index])))
		index++;
	while (map->file[index] && is_only_whitespace(map->file[index]) == false)
	{
		map->map_2d[nb_lines++] = map->file[index];
		index++;
	}
	map->map_2d[nb_lines] = NULL;
	suppress_newlines(map->map_2d);
	if (validate_map_continuity(map) != 0)
		return (NULL);
	return (map->map_2d);
}

/**
 * @brief Validate that configuration lines appear before any map lines
 * 
 * @param[in] map map structure containing the file lines
 * @return int 0 if valid, -1 if invalid structure
 */
int	validate_file_structure(t_map *map)
{
	size_t	index;
	uint8_t	config_count;
	bool	map_started;

	index = 0;
	config_count = 0;
	map_started = false;
	while (map->file[index])
	{
		if (is_config_line(map->file[index]) != 0)
		{
			if (map_started)
				return (print_map_validate_error(map, CONFIG_FOUND_AFTER_MAP));
			config_count++;
		}
		else if (!is_only_whitespace(map->file[index]))
		{
			if (config_count < 6)
				return (print_map_validate_error(map, CONFIG_MAP_TOO_SOON));
			map_started = true;
		}
		index++;
	}
	return (0);
}

/**
 * @brief Validate that the map region is continuous with no empty lines
 * This ensures the map is properly closed and prevents leaks
 * 
 * @param[in] map map structure containing the map_2d array
 * @return int 0 if valid, -1 if gaps found in map
 */
int	validate_map_continuity(t_map *map)
{
	size_t	index;

	if (!map || !map->map_2d)
		return (-1);
	index = 0;
	while (map->map_2d[index])
	{
		if (is_only_whitespace(map->map_2d[index])
			|| ft_strlen(map->map_2d[index]) == 0)
		{
			ft_dprintf(2, RED "Error" RESET
				"\nEmpty line found in map at line %zu\n", index + 1);
			ft_dprintf(2, "Map region must be continuous with no empty line\n");
			map->error = -1;
			return (-1);
		}
		index++;
	}
	return (0);
}
