/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 16:17:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include <string.h>
#include <errno.h>

static int	try_to_open_close_map(char *map_name);

/**
 * @brief Check the map structure and try to open the map file.
 * sets error to -1 if an error occurred.
 * 
 * @param map map structure to check and initialize
 * @param map_name map file name to open
 * @return t_map map structure
 */
t_map	ft_map_check(t_map *map, char *map_name)
{
	if (map == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap structure is NULL\n");
		return ((t_map){.error = -1});
	}
	ft_bzero(map, sizeof(t_map));
	if (try_to_open_close_map(map_name) != 1)
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
	ft_print_config(map);
	ft_print_map(map);
	return (*map);
}

/**
 * @brief Try to open the map file specified by map_name.
 * 
 * @param map_name map file name to open
 * @return int 1 OK, 0 if an error occurred
 */
int	try_to_open_close_map(char *map_name)
{
	int	fd;

	if (map_name == NULL)
		return (0);
	fd = safe_open(map_name);
	if (fd < 0)
		return (0);
	if (read(fd, NULL, 0) < 0)
	{
		ft_dprintf(2, RED"Error"RESET"\nRead fd %d: %s\n", fd, strerror(errno));
		safe_close(&fd);
		return (0);
	}
	fd = safe_close(&fd);
	if (fd != 0)
		return (0);
	return (1);
}
