/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:29:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/29 15:41:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void	*ft_memset(void *pointer, int value, size_t count);

#if OPTI_ALIGNMENT_FT == 0
/**
 * @brief Set a memory zone with a value, count times
 *
 * @param pointer memory zone to set
 * @param value value to set
 * @param count number of times to set the value
 * @return void* pointer to the memory zone
 */
void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*new_pointer;
	size_t			index;

	new_pointer = (unsigned char *)pointer;
	index = 0;
	while (count > 0)
	{
		new_pointer[index] = (unsigned char)value;
		index++;
		count--;
	}
	return (pointer);
}
#else

/**
 * @brief Set a memory zone with a value, count times
 * Faster version of ft_memset,
 *
 * @param pointer memory zone to set
 * @param value value to set
 * @param count number of times to set the value
 * @return void* pointer to the memory zone
 */
void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t		i;
	uint8_t		*ptr;
	uint32_t	*ptr32;
	uint32_t	block;

	i = 0;
	ptr = (uint8_t *)pointer;
	while (i < count && ((uintptr_t)(ptr + i) % 4) != 0)
		ptr[i++] = (unsigned char)value;
	ptr32 = (uint32_t *)(void *)(ptr + i);
	block = (uint8_t)value * 0x01010101;
	while (i + 4 <= count)
	{
		*ptr32++ = block;
		i += 4;
	}
	ptr = (uint8_t *)ptr32;
	while (i < count)
		ptr[i++ - ((uintptr_t)ptr - (uintptr_t)pointer)] = (unsigned char)value;
	return (pointer);
}

/**
 * @brief Set a memory zone with a value, count times
 * Faster version of ft_memset, but for 64-bit systems.
 *
 * @param pointer memory zone to set
 * @param value value to set
 * @param count number of times to set the value
 * @return void* pointer to the memory zone
 */
void	*ft_memset64(void *pointer, int value, size_t count)
{
	size_t		i;
	uint8_t		*ptr;
	uint64_t	*ptr64;
	uint64_t	block;

	i = 0;
	ptr = (uint8_t *)pointer;
	while (i < count && ((uintptr_t)(ptr + i) % 4) != 0)
		ptr[i++] = (unsigned char)value;
	ptr64 = (uint64_t *)(void *)(ptr + i);
	block = (uint8_t)value * 0x0101010101010101;
	while (i + 8 <= count)
	{
		*ptr64++ = block;
		i += 8;
	}
	ptr = (uint8_t *)ptr64;
	while (i < count)
		ptr[i++ - ((uintptr_t)ptr - (uintptr_t)pointer)] = (unsigned char)value;
	return (pointer);
}
#endif
