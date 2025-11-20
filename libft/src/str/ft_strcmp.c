/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:16:03 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 18:42:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strcmp(const char *first, const char *second);

/**
 * @brief Find differences between first and second
 *
 * @param first first string to compare
 * @param second second string to compare
 * @return int value of first - second
 */

int	ft_strcmp(const char *first, const char *second)
{
	size_t	index;

	index = 0;
	while (first[index] != '\0' && second[index] != '\0'
		&& first[index] == second[index])
		index++;
	return ((unsigned char)first[index] - (unsigned char)second[index]);
}
