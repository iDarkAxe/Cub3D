/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posvec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:11:24 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/06 11:19:35 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

int	posvecremove(t_posvec *vec, size_t index, t_pos2 *result)
{
	size_t	i;

	if (index >= vec->len)
		return (0);
	*result = vec->data[index];
	i = index;
	while (i < vec->len - 1)
	{
		vec->data[i] = vec->data[i + 1];
		i++;
	}
	vec->len--;
	return (1);
}
