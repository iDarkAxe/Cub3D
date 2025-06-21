/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:05:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/21 15:09:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

static void	free_array(char **array);
static int	has_line_an_error(t_map *map, char **array, const char *line);

t_map	ft_check_floor_ceiling(t_map *map)
{
	char	**split;

	if (!map)
		return ((t_map){.error = -1});
	split = ft_split(&map->config[4][2], ',');
	if (!split || !split[0] || !split[1] || !split[2])
		map->error = 1;
	if (has_line_an_error(map, split, "floor") == 1)
		return (*map);
	map->textures.floor.s_rgb.red = (unsigned char)ft_atoi(split[0]);
	map->textures.floor.s_rgb.green = (unsigned char)ft_atoi(split[1]);
	map->textures.floor.s_rgb.blue = (unsigned char)ft_atoi(split[2]);
	free_array(split);
	split = ft_split(&map->config[5][2], ',');
	if (!split || !split[0] || !split[1] || !split[2])
		map->error = 1;
	if (has_line_an_error(map, split, "ceiling") == 1)
		return (*map);
	map->textures.ceiling.s_rgb.red = (unsigned char)ft_atoi(split[0]);
	map->textures.ceiling.s_rgb.green = (unsigned char)ft_atoi(split[1]);
	map->textures.ceiling.s_rgb.blue = (unsigned char)ft_atoi(split[2]);
	free_array(split);
	ft_print_floor_ceiling(map);
	return (*map);
}

/**
 * @brief Check if a line has an error
 * the split shouldn't contain more than 3 strings
 *
 * @param map map structure
 * @param array array of strings
 * @param line line to check
 * @return int 1 has an error, 0 otherwse
 */
int	has_line_an_error(t_map *map, char **array, const char *line)
{
	if (!map || map->error != 0)
		return (1);
	if (array && array[0] && array[1] && array[2] && array[3])
	{
		ft_dprintf(2,
			RED "Error" RESET "\nColor of %s has too many parameters\n",
			line);
		free_array(array);
		map->error = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Free array of strings
 *
 * @param array array of strings
 */
void	free_array(char **array)
{
	size_t	index;

	if (array == NULL)
		return ;
	index = 0;
	while (array && array[index])
	{
		free(array[index]);
		array[index] = NULL;
		index++;
	}
	free(array);
	array = NULL;
}
