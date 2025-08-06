/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:16:17 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/06 11:23:02 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_printf.h"
#include "libft.h"
#include "maze.h"
#include <stdlib.h>
#include <time.h>

// Simple Fisher-Yates shuffle
static void	shuffle_array(int *arr, int len)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < len)
	{
		j = rand() % len;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		i++;
	}
}

static int	grow_the_tree(t_map_raoul *map, t_posvec *vec)
{
	static int	dirs[4] = {MAZE_N, MAZE_S, MAZE_E, MAZE_W};
	int			i;
	t_pos2		pos;
	t_pos2		next;

	shuffle_array(dirs, 4);
	posvecremove(vec, rand() % vec->len, &pos);
	i = 0;
	while (i < 4)
	{
		next.x = pos.x + maze_dir_x(dirs[i]);
		next.y = pos.y + maze_dir_y(dirs[i]);
		if (next.x >= 0 && next.y >= 0 && next.x < (int)map->width
			&& next.y < (int)map->height
			&& map->walls[next.y * map->width + next.x] == 0)
		{
			map->walls[pos.y * map->width + pos.x] |= dirs[i];
			map->walls[next.y * map->width + next.x] |= maze_dir_opp(dirs[i]);
			if (posvecpush(vec, next) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

static void	translate_cells(int *dirs, t_pos2 dsize, int *walls, t_pos2 wsize)
{
	int		i;
	int		count;
	t_pos2	dpos;
	t_pos2	wpos;
	int		j;

	i = 0;
	count = dsize.x * dsize.y;
	ft_printf("Max index is %d\n", (dsize.x * 2 + 1) * (dsize.y * 2 + 1));
	while (i < count)
	{
		dpos = (t_pos2){i % dsize.x, i / dsize.x};
		wpos = (t_pos2){dpos.x * 2 + 1, dpos.y * 2 + 1};
		j = wpos.y * wsize.x + wpos.x;
		walls[j] = 0;
		wpos.x += maze_dir_x(dirs[i]);
		j = wpos.y * wsize.x + wpos.x;
		walls[j] = 0;
		wpos.x -= maze_dir_x(dirs[i]);
		wpos.y += maze_dir_y(dirs[i]);
		j = wpos.y * wsize.x + wpos.x;
		walls[j] = 0;
		i++;
	}
}

static int	translate_map(t_map_raoul *map)
{
	int		*walls;

	walls = malloc((map->width * 2 + 1) * (map->height * 2 + 1) * sizeof(int));
	if (walls == NULL)
		return (0);
	ft_memset(walls, 1, sizeof(int) * (map->width * 2 + 1)
		* (map->height * 2 + 1));
	translate_cells(map->walls, (t_pos2){(int)map->width, (int)map->height},
		walls, (t_pos2){(int)map->width * 2 + 1, (int)map->height * 2 + 1});
	free(map->walls);
	map->walls = walls;
	map->width = map->width * 2 + 1;
	map->height = map->height * 2 + 1;
	return (1);
}

int	cub_growing_tree(t_map_raoul *map)
{
	t_posvec	*vec;

	srand(time(NULL));
	vec = posvecnew((map->width * map->height) / 2);
	if (vec == NULL)
		return (0);
	posvecpush(vec, (t_pos2){0, 0});
	while (vec->len > 0)
		if (grow_the_tree(map, vec) == 0)
			return (0);
	posvecfree(vec);
	return (translate_map(map));
}
