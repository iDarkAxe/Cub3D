/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:50:42 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/09 11:17:11 by ppontet          ###   ########lyon.fr   */
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

int	cub_generate_maze(t_map_raoul *map, char *gen)
{
	ft_srand(get_time_ms());
	if (!cub_parse_generation_arg(gen, &map->width, &map->height))
		return (0);
	if (map->walls)
		free(map->walls);
	map->walls = ft_calloc(map->width * map->height, sizeof(int));
	map->start_pos = (t_pos2){(ft_rand() % map->width) * 2 + 1,
		(ft_rand() % map->height) * 2 + 1};
	map->start_angle = random_float(PI * 2);
	if (map->walls == NULL)
		return (0);
	if (cub_growing_tree(map) == 0)
	{
		free(map->walls);
		return (0);
	}
	return (1);
}
