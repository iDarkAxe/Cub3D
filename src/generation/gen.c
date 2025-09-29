/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:50:42 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/29 15:15:06 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "libft.h"
#include "maze.h"
#include <stdlib.h>

static float	random_float(float a)
{
	return ((float)ft_rand() / (float)(FT_RAND_MAX / a));
}

t_map_raoul	*cub_new_map_from_dimensions(char *dimensions)
{
	t_map_raoul	*map;

	map = ft_calloc(1, sizeof(t_map_raoul));
	if (!map)
		return (NULL);
	if (!cub_parse_generation_arg(dimensions, &map->width, &map->height))
	{
		free(map);
		return (NULL);
	}
	map->walls = ft_calloc(map->width * map->height, sizeof(int));
	if (map->walls == NULL)
	{
		free(map);
		return (NULL);
	}
	map->start_pos = (t_pos2){(ft_rand() % map->width) * 2 + 1, (ft_rand()
			% map->height) * 2 + 1};
	map->start_angle = random_float(PI * 2);
	map->door = (t_pos2){-1, -1};
	map->key = (t_pos2){-1, -1};
	return (map);
}
