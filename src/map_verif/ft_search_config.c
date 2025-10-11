/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:12:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/08 14:57:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "libft.h"
#include <stdlib.h>

static t_map	ft_check_textures(t_map *map);
static void		*store_textures_names(t_map *map, char *str, size_t index);

size_t	is_config_line(char *line)
{
	static const char *const	config_str[] = {"NO ", "SO ", "WE ", "EA ",
		"F ", "C ", NULL};
	size_t						i;

	i = 0;
	while (config_str[i])
	{
		if (ft_strncmp(line, config_str[i], ft_strlen(config_str[i])) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

char	**fill_config_region(t_map *map)
{
	size_t	index;
	size_t	ret;
	int		nbr_config;

	if (!map || !map->file)
		return (NULL);
	index = 0;
	nbr_config = 0;
	while (map->error == 0 && map->file[index])
	{
		ret = is_config_line(map->file[index]);
		if (ret != 0 && ret > 0 && map->config[ret - 1] != NULL)
			print_map_error(map, CONFIG_ALREADY_STORED);
		if (map->error == 0 && ret != 0 && ret > 0)
		{
			map->config[ret - 1] = map->file[index];
			nbr_config++;
		}
		if (nbr_config > 6)
			print_map_error(map, CONFIG_TOO_MANY_PARAMETERS);
		index++;
	}
	if (nbr_config != 6)
		print_map_error(map, CONFIG_MISSING_PARAMETERS);
	return (map->config);
}

t_map	ft_check_config(t_map *map)
{
	if (!map || !map->file)
		return ((t_map){.error = -1});
	*map = ft_check_textures(map);
	if (map->error != 0)
		return (*map);
	*map = ft_check_floor_ceiling(map);
	if (map->error != 0)
		return (*map);
	return (*map);
}

t_map	ft_check_textures(t_map *map)
{
	char	*str;
	size_t	index;
	int		ret;

	if (!map || map->textures.north.path || map->textures.south.path
		|| map->textures.west.path || map->textures.east.path)
		return ((t_map){.error = -1});
	index = 0;
	while (map->error == 0 && map->config[index] && index < 4)
	{
		str = ft_strtrim(&map->config[index][3], " \t\v\n\f\r");
		ret = try_to_open_close_file(str);
		if (ret != 1 || !store_textures_names(map, str, index))
		{
			if (str)
				free(str);
			map->error = 1;
			return (*map);
		}
		index++;
	}
	return (*map);
}

/**
 * @brief Store the textures names in the structure
 *
 * @param map map structure
 * @return char* NULL if error, OK otherwise
 */
void	*store_textures_names(t_map *map, char *str, size_t index)
{
	if (!map || !str)
		return (NULL);
	if (index == 0)
		map->textures.north.path = str;
	else if (index == 1)
		map->textures.south.path = str;
	else if (index == 2)
		map->textures.west.path = str;
	else if (index == 3)
		map->textures.east.path = str;
	else
		return (NULL);
	return (str);
}
