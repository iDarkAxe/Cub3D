/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:33:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/08 16:22:06 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stddef.h>
# include <unistd.h>

/*
** Only the following conversion specifiers are handled:
** %%: print a percentage
** %c: char
** %s: string
** %p: pointer (in hexadecimal)
** %d: signed int
** %i: signed int
** %u: unsigned int
** %x: unsigned int in hexadecimal (lowercase)
** %X: unsigned int in hexadecimal (uppercase)
**
** Currently, no flags, width, precision or length modifiers are handled.
*/

int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);

#endif
