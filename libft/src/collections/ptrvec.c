/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:44:38 by rdesprez          #+#    #+#             */
/*   Updated: 2025/02/05 19:33:54 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_collections.h"
#include <malloc.h>

t_ptrvec	*ptrvecnew(size_t size)
{
	t_ptrvec	*vec;

	vec = malloc(sizeof(t_ptrvec));
	if (vec == NULL)
		return (NULL);
	vec->data = malloc(sizeof(void *) * size);
	if (vec->data == NULL)
	{
		free(vec);
		return (NULL);
	}
	vec->capacity = size;
	vec->len = 0;
	return (vec);
}

int	ptrvecpush(t_ptrvec *vec, void *data)
{
	void	*tmp;

	if (vec->len == vec->capacity)
	{
		tmp = malloc(sizeof(void *) * (vec->capacity * 2));
		if (tmp == NULL)
			return (0);
		ft_memcpy(tmp, vec->data, sizeof(void *) * vec->capacity);
		free(vec->data);
		vec->capacity *= 2;
		vec->data = tmp;
	}
	vec->data[vec->len] = data;
	vec->len++;
	return (1);
}

void	*ptrvecpop(t_ptrvec *vec)
{
	if (vec->len == 0)
		return (NULL);
	vec->len--;
	return (vec->data[vec->len]);
}

void	ptrvecfree(t_ptrvec *vec, void (*free_fn)(void *))
{
	size_t	i;

	i = 0;
	while (i < vec->len)
	{
		if (free_fn)
			free_fn(vec->data[i]);
		i++;
	}
	free(vec->data);
	free(vec);
}
