/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/28 17:53:25 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static bool		is_only_whitespace(const char *str);
static size_t	count_map_size(t_map *map);

static void	suppress_newlines(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '\n')
				lines[i][j] = 0;
			j++;
		}
		i++;
	}
}

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
	size_t	index;
	int		nb_lines;

	if (!map || !map->file)
		return (NULL);
	map->map_2d = malloc(sizeof(char *) * (count_map_size(map) - 6 + 1));
	if (!map->map_2d)
		return (NULL);
	nb_lines = 0;
	index = 0;
	while (map->file[index] && map->error == 0)
	{
		if (is_config_line(map->file[index]) == 0
			&& is_only_whitespace(map->file[index]) == false)
		{
			map->map_2d[nb_lines] = map->file[index];
			nb_lines++;
		}
		index++;
	}
	map->map_2d[nb_lines] = NULL;
	suppress_newlines(map->map_2d);
	return (map->map_2d);
}

/**
 * @brief Check if the string contains only whitespace characters
 *
 * @param str string to check
 * @return bool 1 all whitespace, 0 otherwise
 */
bool	is_only_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (false);
	while (str[i])
	{
		if (!ft_isspace((unsigned char)str[i]))
			return (false);
		i++;
	}
	return (true);
}
