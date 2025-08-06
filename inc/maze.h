/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:23:53 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/05 20:16:17 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAZE_H
# define MAZE_H

# include "data_structure.h"
# include <stddef.h>

# define MAZE_N 1
# define MAZE_S 2
# define MAZE_E 4
# define MAZE_W 8

int			maze_dir_x(int dir);
int			maze_dir_y(int dir);
int			maze_dir_opp(int dir);

typedef struct s_posvec
{
	t_pos2	*data;
	size_t	len;
	size_t	capacity;
}	t_posvec;

t_posvec	*posvecnew(size_t size);
int			posvecpush(t_posvec *vec, t_pos2 data);
int			posvecpop(t_posvec *vec, t_pos2 *pos);
void		posvecfree(t_posvec *vec);

int			cub_generate_maze(t_map_raoul *map, char *gen);

#endif
