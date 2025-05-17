/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:33:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/18 19:44:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

/**
 * @file ft_print.h
 * @brief Header file for the print functions.
 *
*/

# include <unistd.h>

/**
 * @defgroup Print Print functions
 * @brief All the functions used to print.
 * @{
 */

/**
 * @brief Print numbers in a file descriptor.
 * 
 * @param n Number to print.
 * @param fd File descriptor
 * @return ssize_t number of printed characters.
 */
ssize_t	ft_putnbr_fd(long long n, int fd);

/**
 * @brief Print a pointer in a file descriptor.
 * 
 * @param ptr Pointer to print.
 * @param fd File descriptor.
 * @return ssize_t number of printed characters.
 */
ssize_t	ft_putpointer_fd(unsigned long ptr, int fd);
/** @} */

#endif
