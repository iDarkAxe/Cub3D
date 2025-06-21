/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 16:24:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	is_only_whitespace(const char *str);
static size_t	count_map_size(t_map *map);

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
		if (is_only_whitespace(map->file[index]) == FALSE)
			count++;
		index++;
	}
	return (count);
}

char	**fill_map_region(t_map *map)
{
	size_t	index;
	int		nb_lines;

	if (!map || !map->file)
		return (NULL);
	map->map = malloc(sizeof(char *) * (count_map_size(map) - 6 + 1));
	if (!map->map)
		return (NULL);
	nb_lines = 0;
	index = 0;
	while (map->file[index] && map->error == 0)
	{
		if (is_config_line(map->file[index]) == 0
			&& is_only_whitespace(map->file[index]) == FALSE)
		{
			map->map[nb_lines] = map->file[index];
			nb_lines++;
		}
		index++;
	}
	map->map[nb_lines] = NULL;
	return (map->map);
}

/**
 * @brief Check if the string contains only whitespace characters
 *
 * @param str string to check
 * @return t_bool 1 all whitespace, 0 otherwise
 */
t_bool	is_only_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (str[i])
	{
		if (!ft_isspace((unsigned char)str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
