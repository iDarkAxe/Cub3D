/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:35:31 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/08 18:21:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>
#include "maze.h"

t_posvec	*posvecnew(size_t nbr_of_elements)
{
	t_posvec	*vec;

	vec = malloc(sizeof(t_posvec));
	if (vec == NULL)
		return (NULL);
	vec->data = malloc(sizeof(t_pos2) * nbr_of_elements);
	if (vec->data == NULL)
	{
		free(vec);
		return (NULL);
	}
	vec->capacity = nbr_of_elements;
	vec->len = 0;
	return (vec);
}

int	posvecpush(t_posvec *vec, t_pos2 data)
{
	t_pos2	*tmp;

	if (vec->len == vec->capacity)
	{
		tmp = malloc(sizeof(t_pos2) * (vec->capacity * 2));
		if (tmp == NULL)
			return (0);
		ft_memcpy(tmp, vec->data, sizeof(t_pos2) * vec->capacity);
		free(vec->data);
		vec->capacity *= 2;
		vec->data = tmp;
	}
	vec->data[vec->len] = data;
	vec->len++;
	return (1);
}

int	posvecpop(t_posvec *vec, t_pos2 *pos)
{
	if (vec->len == 0)
		return (0);
	vec->len--;
	if (pos)
		*pos = vec->data[vec->len];
	return (1);
}

int	posvecremove(t_posvec *vec, size_t index, t_pos2 *result)
{
	if (index >= vec->len)
		return (0);
	*result = vec->data[index];
	ft_memmove(&vec->data[index], &vec->data[index + 1],
		(vec->len - index - 1) * sizeof(t_pos2));
	vec->len--;
	return (1);
}

void	posvecfree(t_posvec *vec)
{
	free(vec->data);
	free(vec);
}
