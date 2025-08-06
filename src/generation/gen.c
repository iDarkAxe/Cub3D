/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:50:42 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/06 10:33:45 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "libft.h"
#include <stdlib.h>

int	cub_parse_generation_arg(char *gen, size_t *width, size_t *height);
int	cub_growing_tree(t_map_raoul *map);

int	cub_generate_maze(t_map_raoul *map, char *gen)
{
	if (!cub_parse_generation_arg(gen, &map->width, &map->height))
		return (0);
	map->walls = ft_calloc(map->width * map->height, sizeof(int));
	if (map->walls == NULL)
		return (0);
	if (cub_growing_tree(map) == 0)
	{
		free(map->walls);
		return (0);
	}
	return (1);
}
