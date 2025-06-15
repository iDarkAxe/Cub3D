/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:15:16 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/15 13:19:51 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include "get_next_line.h"

size_t	count_file_lines(char *file_name)
{
	int		fd;
	char	*line;
	size_t	line_count;

	if (file_name == NULL)
		return (0);
	fd = safe_open(file_name);
	if (fd < 0)
		return (0);
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	safe_close(&fd);
	return (line_count);
}

char	**read_file_lines(t_map *map, char *map_name)
{
	int		fd;
	size_t	index;

	if (!map)
		return (NULL);
	map->file_nb_lines = count_file_lines(map_name);
	map->file = malloc(sizeof(char *) * (map->file_nb_lines + 1));
	if (map->file == NULL)
		return (NULL);
	fd = safe_open(map_name);
	if (fd < 0)
		return (0);
	index = 0;
	while (map->file_nb_lines > index)
	{
		map->file[index] = get_next_line(fd);
		if (map->file[index] == NULL)
			break ;
		index++;
	}
	map->file[index] = NULL;
	safe_close(&fd);
	return (map->file);
}
