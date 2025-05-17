/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:03:57 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/18 19:44:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static ssize_t	ft_putnbr_hex_pointer(unsigned long nbr, const char *base,
		int fd)
{
	ssize_t	temp;

	temp = 0;
	if (nbr >= 16)
	{
		temp += ft_putnbr_hex_pointer(nbr / 16, base, fd);
		temp += ft_putnbr_hex_pointer(nbr % 16, base, fd);
	}
	else
		temp += write(fd, &base[nbr], 1);
	return (temp);
}

/**
 * @brief Print pointer adress
 *
 * @param nbr Number to be printed
 * @return ssize_t number of char printed
 */
ssize_t	ft_putpointer_fd(unsigned long nbr, int fd)
{
	if (!nbr)
		return (write(fd, "(nil)", 5));
	if (write(fd, "0x", 2) != -1)
		return (ft_putnbr_hex_pointer(nbr, "0123456789abcdef\0", fd) + 2);
	return (-1);
}

/**
 * @brief Write the int 'n' on the given file descriptor
 *	Works with recursion
 * @param n number to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
static ssize_t	ft_putnbr_recursive_fd(long long n, int fd)
{
	ssize_t	count_printed;
	char	temp;

	count_printed = 0;
	if (n >= 10)
		count_printed += ft_putnbr_fd(n / 10, fd);
	temp = n % 10 + '0';
	count_printed += write(fd, &temp, 1);
	return (count_printed);
}

/**
 * @brief Write the int 'n' on the given file descriptor
 *
 * @param n number to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
ssize_t	ft_putnbr_fd(long long n, int fd)
{
	ssize_t	count_printed;

	count_printed = 0;
	if (n < 0)
	{
		n = -n;
		count_printed += write(fd, "-", 1);
	}
	return (count_printed + ft_putnbr_recursive_fd(n, fd));
}
