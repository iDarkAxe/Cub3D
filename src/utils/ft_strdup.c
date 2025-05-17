/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:51:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:14:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

// TODO vérifier antériorité et compatibilité

char	*ft_strdup(const char *source);

char	*ft_strdup(const char *source)
{
	char	*pointer;
	size_t	count;
	size_t	index;

	count = 0;
	while (source[count] != '\0')
		count++;
	pointer = malloc(sizeof(char) * (count + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (count > 0)
	{
		pointer[index] = source[index];
		index++;
		count--;
	}
	pointer[index] = '\0';
	return (pointer);
}
