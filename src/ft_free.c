/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 15:30:33 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include <stdlib.h>

void	ft_free_file(t_map *map);

void	ft_free_file(t_map *map)
{
	size_t	index;

	if (map == NULL)
		return ;
	if (map->file != NULL)
	{
		index = 0;
		while (map->file[index])
			free(map->file[index++]);
		free(map->file);
		map->file = NULL;
	}
	if (map->map != NULL)
	{
		free(map->map);
		map->map = NULL;
	}
	map->file_nb_lines = 0;
}
