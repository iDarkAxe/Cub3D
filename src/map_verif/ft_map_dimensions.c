/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_dimensions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:20:32 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:00:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_print.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static void	update_line_info(t_map_size *map, char character)
{
	map->line_len++;
	if (character == '\n')
	{
		if (map->count_line == 0)
			map->prev_line_len = map->line_len;
		else if (map->line_len != map->prev_line_len)
			map->error_occured = 1;
		map->line_len = 0;
		map->count_line++;
	}
}

t_map_size	dimensions_verif(char *map_name)
{
	char		character;
	ssize_t		ret;
	t_map_size	map;

	map = (t_map_size){0, map_name, 0, 0, 0, 0};
	map.fd = open(map.map_name, O_RDONLY);
	if (map.fd == -1)
		map.error_occured = 2;
	while (map.error_occured == 0)
	{
		ret = read(map.fd, &character, 1);
		if (ret == -1 || (ret == 0 && map.line_len + 1 != map.prev_line_len))
			map.error_occured = 1;
		if (ret == 0)
			break ;
		update_line_info(&map, character);
	}
	if (map.error_occured != 2)
		close(map.fd);
	return (map);
}

t_map	*check_borders(t_map_size map_size)
{
	size_t	i;
	t_map	*map;

	if (map_size.error_occured != 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (map == NULL || fill_map(map, map_size) == NULL)
		return (NULL);
	map->error = 0;
	i = 0;
	while ((i < map->width || i < map->height) && map->error != -1)
	{
		if (i < map->width && (map->map[0][i] != '1'
			|| map->map[map->height][i] != '1'))
			map->error = -1;
		else if (i < map->height && (map->map[i][0] != '1'
			|| map->map[i][map->width - 1] != '1'))
			map->error = -1;
		i++;
	}
	map->collectibles = find_max_collectibles(map);
	map->exit = find_position(map, 'E');
	return (map);
}
