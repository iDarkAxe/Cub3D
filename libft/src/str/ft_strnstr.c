/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:06:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 18:18:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
* @brief Search a substring in a bigger string,
	up to len position in string
*
* @param big string to search in
* @param little	string to search
* @param len max size of big
* @return char* pointer to the first occurence of little in big
*/
const char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_size;
	size_t	count;

	count = 0;
	little_size = ft_strlen(little);
	if (little_size == 0 || little == big)
		return (&big[0]);
	if (len == 0 || *big == '\0' || ft_strlen(big) < little_size
		|| len < little_size)
		return (NULL);
	while (big[count] != '\0' && count <= (len - little_size))
	{
		if (ft_strncmp(&big[count], little, little_size) == 0)
			return (&big[count]);
		count++;
	}
	if (count > (len - little_size))
		return (NULL);
	return (&big[0]);
}
