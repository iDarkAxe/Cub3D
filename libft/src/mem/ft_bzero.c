/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:33:04 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 18:17:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n);

/**
 * @brief Set at 0, the n first bytes at the pointer adress
 *
 * @param s pointer to the memory to set
 * @param n number of bytes to set at 0
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return ;
}
