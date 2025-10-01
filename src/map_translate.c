/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:35:38 by rdesprez          #+#    #+#             */
/*   Updated: 2025/10/01 16:35:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "data_structure.h"
#include "libft.h"
#include <malloc.h>

static void	get_map_max_size(char **lines, size_t *width, size_t *height)
{
	int	i;

	i = 0;
	*width = 0;
	while (lines[i])
	{
		*width = max(ft_strlen(lines[i]), *width);
		i++;
	}
	*height = i;
}

static int	define_start_player_state(t_map_raoul *map, t_pos2 pos, float angle)
{
	map->start_pos = pos;
	map->start_angle = angle;
	return (0);
}

static int	interpret_tile(t_map_raoul *map, t_pos2 pos, char tile)
{
	if (tile == '0')
		return (0);
	if (tile == '1')
		return (1);
	if (tile == 'N')
		return (define_start_player_state(map, pos, 3 * PI / 2.f));
	if (tile == 'S')
		return (define_start_player_state(map, pos, PI / 2.f));
	if (tile == 'E')
		return (define_start_player_state(map, pos, 0.f));
	if (tile == 'W')
		return (define_start_player_state(map, pos, PI));
	return (0);
}

static void	copy_map(char **lines, t_map_raoul *map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (lines[i])
	{
		j = 0;
		len = ft_strlen(lines[i]);
		while (j < len)
		{
			map->walls[i * map->width + j] = interpret_tile(map, (t_pos2){j, i},
					lines[i][j]);
			j++;
		}
		i++;
	}
}

int	cub_translate_map(t_data *data)
{
	data->map.map = malloc(sizeof(t_map_raoul));
	if (data->map.map == NULL)
		return (0);
	get_map_max_size(data->map.map_2d, &data->map.map->width,
		&data->map.map->height);
	data->map.map->walls = ft_calloc(data->map.map->width
			* data->map.map->height, sizeof(int));
	if (data->map.map->walls == NULL)
	{
		free(data->map.map);
		data->map.map = NULL;
		return (0);
	}
	copy_map(data->map.map_2d, data->map.map);
	data->map.map->door = (t_pos2){-1, -1};
	data->map.map->key = (t_pos2){-1, -1};
	return (1);
}
