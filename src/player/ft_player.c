/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:40:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:00:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_keys.h"
#include "so_long.h"

// TODO pas de collectibles en théorie

static int	ft_collectibles_handler(t_map *map, t_mlx *mlx,
		t_coordinates new_pos)
{
	if (map->exit.x == new_pos.x && map->exit.y == new_pos.y
		&& map->collectibles == 0)
		return (0);
	if (map->map[new_pos.y][new_pos.x] == 'C')
		map->collectibles--;
	(void)mlx;
	map->map[new_pos.y][new_pos.x] = 'P';
	return (1);
}

void	can_player_move(t_mlx *mlx, t_map *map, int direction)
{
	t_coordinates	old_pos;
	t_coordinates	new_pos;

	old_pos = find_position(map, 'P');
	map->map[old_pos.y][old_pos.x] = 'p';
	if (direction == KEY_RIGHT && map->map[old_pos.y][old_pos.x + 1] != '1')
		new_pos = (t_coordinates){old_pos.x + 1, old_pos.y};
	else if (direction == KEY_LEFT && map->map[old_pos.y][old_pos.x - 1] != '1')
		new_pos = (t_coordinates){old_pos.x - 1, old_pos.y};
	else if (direction == KEY_DOWN && map->map[old_pos.y + 1][old_pos.x] != '1')
		new_pos = (t_coordinates){old_pos.x, old_pos.y + 1};
	else if (direction == KEY_UP && map->map[old_pos.y - 1][old_pos.x] != '1')
		new_pos = (t_coordinates){old_pos.x, old_pos.y - 1};
	else
	{
		map->map[old_pos.y][old_pos.x] = 'P';
		return ;
	}
	if (ft_collectibles_handler(map, mlx, new_pos) == 0)
	{
		write(1, "You won!\n", 9);
		close_window((void *)mlx);
	}
	map->map[old_pos.y][old_pos.x] = '0';
}
