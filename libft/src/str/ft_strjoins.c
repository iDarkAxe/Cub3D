/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:56:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 18:18:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static size_t	count_len_array(char *str[]);

/**
 * @brief Allocates a new string, and returns the result of
 * a concatenation of all the strings from the array
 * last argument needs to be NULL.
 *
 * @param array Array of strings
 * @return char* new string
 */
char	*ft_strjoins(char **array)
{
	size_t	count;
	size_t	index;
	size_t	size;
	char	*new_str;

	if (array == NULL || array[0] == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * (count_len_array(array) + 1));
	if (new_str == NULL)
		return (NULL);
	index = 0;
	count = 0;
	while (array != NULL && array[count] != NULL)
	{
		size = ft_strlen(array[count]);
		ft_memcpy(&new_str[index], array[count++], size);
		index += size;
	}
	new_str[index] = '\0';
	return (new_str);
}

static size_t	count_len_array(char *array[])
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (array != NULL && array[index] != NULL)
		count += ft_strlen(array[index++]);
	return (count);
}
