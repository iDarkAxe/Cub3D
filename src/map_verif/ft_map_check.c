/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/17 13:13:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include <stdbool.h>

static int	has_player_already_been_found(char **map, t_coordinates pos,
				bool *player);
static int	check_autorized_chars(char **map);

t_map	ft_map_check_dimensions(t_map *map, char *map_name)
{
	if (map == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap structure is NULL\n");
		return ((t_map){.error = -1});
	}
	ft_bzero(map, sizeof(t_map));
	if (try_to_open_close_file(map_name) != 1)
	{
		map->error = -1;
		return (*map);
	}
	if (read_file_lines(map, map_name) == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nFailed to read map file\n");
		map->error = -1;
		return (*map);
	}
	if (fill_config_region(map) == NULL || map->error != 0)
		return (*map);
	if (fill_map_region(map) == NULL || map->error != 0)
		return (*map);
	*map = check_map_chars_borders(map);
	if (map && map->error != 0)
		return (*map);
	return (*map);
}

t_map	check_map_chars_borders(t_map *map)
{
	if (map == NULL || map->error != 0)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap structure is NULL\n");
		return ((t_map){.error = -1});
	}
	if (check_autorized_chars(map->map) == 0)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap->map has unautorized chars\n");
		map->error = -1;
		return (*map);
	}
	if (validate_map(map) != 0)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap->map is invalid\n");
		map->error = -1;
		return (*map);
	}
	return (*map);
}

/**
 * @brief Check if the player has already been found
 * if first time, set player as true
 * if not, return 1 as error
 * 
 * @param map array of strings representing map
 * @param pos position tested
 * @param player player boolean
 * @return int 0 OK, error otherwise
 */
int	has_player_already_been_found(char **map, t_coordinates pos, bool *player)
{
	if (!map)
		return (1);
	if (pos.x == 0 && pos.y == 0)
		*player = false;
	if (ft_strchr("NSEW", map[pos.y][pos.x]) == NULL)
		return (0);
	else
	{
		if (*player == false)
			*player = true;
		else
		{
			ft_dprintf(2, RED "Error" RESET
				"\nPlayer already found, duplicate '%c' is at x:%u y:%u\n",
				map[pos.y][pos.x], (unsigned int)pos.x, (unsigned int)pos.y);
			return (1);
		}
		return (0);
	}
}

/**
 * @brief Check if all chars of map are autorized or not
 * 
 * @param map array of strings representing map
 * @return int 1 OK, error otherwise
 */
int	check_autorized_chars(char **map)
{
	t_coordinates	pos;
	bool			player;

	if (!map)
		return (0);
	pos = (t_coordinates){.x = 0, .y = 0};
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if (ft_strchr("01NSEW", map[pos.y][pos.x]) == NULL
				&& ft_isspace(map[pos.y][pos.x]) == 0)
			{
				ft_dprintf(2, RED "Error" RESET "\nCulprit char "
					RED "'%c'" RESET" is unautorized\n", map[pos.y][pos.x]);
				return (0);
			}
			if (has_player_already_been_found(map, pos, &player) == 1)
				return (0);
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}
