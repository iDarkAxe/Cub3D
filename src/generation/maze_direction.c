/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:22:49 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/05 20:02:59 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

int	maze_dir_x(int dir)
{
	if (dir & MAZE_E)
		return (1);
	if (dir & MAZE_W)
		return (-1);
	return (0);
}

int	maze_dir_y(int dir)
{
	if (dir & MAZE_N)
		return (-1);
	if (dir & MAZE_S)
		return (1);
	return (0);
}

int	maze_dir_opp(int dir)
{
	if (dir & MAZE_N)
		return (MAZE_S);
	if (dir & MAZE_S)
		return (MAZE_N);
	if (dir & MAZE_W)
		return (MAZE_E);
	if (dir & MAZE_E)
		return (MAZE_W);
	return (0);
}
