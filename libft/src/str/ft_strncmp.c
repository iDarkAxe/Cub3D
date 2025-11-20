/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:16:03 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 18:42:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *first, const char *second, size_t length);

/**
 * @brief Find differences between first and second
 *
 * @param first first string to compare
 * @param second second string to compare
 * @param length number of characters to compare
 * @return int value of first - second
 */

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	index;

	index = 0;
	if (length == 0)
		return (0);
	while (index < (length - 1) && first[index] != '\0' && second[index] != '\0'
		&& first[index] == second[index])
		index++;
	return ((unsigned char)first[index] - (unsigned char)second[index]);
}
