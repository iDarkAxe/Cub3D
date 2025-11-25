/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:34:00 by rdesprez          #+#    #+#             */
/*   Updated: 2025/11/25 09:55:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include "maze.h"
#include <math.h>

static int	is_empty(t_map_raoul *map, size_t x, size_t y)
{
	if (x == 0 || x >= map->width || y == 0 || y >= map->height)
		return (0);
	return (map->walls[y * map->width + x] == 0);
}

static int	find_deadends(t_map_raoul *map, t_posvec *deadends)
{
	size_t	x;
	size_t	y;
	int		c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_empty(map, x, y))
			{
				c = is_empty(map, x - 1, y) + is_empty(map, x + 1, y)
					+ is_empty(map, x, y - 1) + is_empty(map, x, y + 1);
				if (c == 1)
					if (posvecpush(deadends, (t_pos2){x, y}) == 0)
						return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static double	distance(t_pos2 p1, t_pos2 p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

static t_pos2	place_random_triangle(double min_dist, t_posvec *deadends,
	t_pos2 p1, t_pos2 p2)
{
	t_pos2	pos;
	t_pos2	farthest;
	double	far_dist;
	int		attempts;
	double	tmp[2];

	attempts = 0;
	far_dist = 0;
	farthest = (t_pos2){0, 0};
	while (attempts < 10000)
	{
		pos = deadends->data[ft_rand() % deadends->len];
		tmp[0] = distance(p1, pos);
		tmp[1] = distance(p2, pos);
		if (tmp[0] > min_dist && tmp[1] > min_dist)
			return (pos);
		if (tmp[0] > far_dist && tmp[1] > far_dist)
		{
			far_dist = mind(tmp[0], tmp[1]);
			farthest = pos;
		}
		attempts++;
	}
	return (farthest);
}

int	cub_spawn_objects(t_map_raoul *map, int key)
{
	t_posvec	*deadends;
	double		min_dist;
	t_pos2		pos;

	deadends = posvecnew(map->width * map->height / 4);
	if (deadends == NULL)
		return (0);
	if (find_deadends(map, deadends) == 0)
	{
		posvecfree(deadends);
		return (0);
	}
	min_dist = sqrt(pow(map->width * 0.5, 2) + pow(map->height * 0.5, 2));
	pos = place_random_triangle(min_dist, deadends, map->start_pos,
			map->start_pos);
	map->walls[pos.y * map->width + pos.x] = -1;
	map->door = pos;
	if (key)
	{
		pos = place_random_triangle(min_dist, deadends, map->start_pos, pos);
		map->walls[pos.y * map->width + pos.x] = -2;
		map->key = pos;
	}
	posvecfree(deadends);
	return (1);
}
