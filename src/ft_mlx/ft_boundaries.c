/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boundaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:57:51 by ppontet           #+#    #+#             */
/*   Updated: 2025/12/16 19:58:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"

void	pos_boundary(t_pos2 *pos, const t_pos2 limit)
{
	if (pos->x > limit.x)
		pos->x = limit.x;
	if (pos->y > limit.y)
		pos->y = limit.y;
	if (pos->x < 0)
		pos->x = 0;
	if (pos->y < 0)
		pos->y = 0;
}
