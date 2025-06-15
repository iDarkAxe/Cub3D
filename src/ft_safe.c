/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:43:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/15 10:57:29 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_print.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	safe_open(char *file_name);
int	safe_close(int *fd);

/**
 * @brief Try to open the map file specified by map_name.
 * 
 * @param file_name file name to open
 * @return int fd=OK, -1 if an error occurred
 */
int	safe_open(char *file_name)
{
	int	fd;

	if (file_name == NULL)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		fd = errno;
		ft_dprintf(2, RED"Error"RESET"\nFailed to open file '%s'\n", file_name);
		ft_dprintf(2, "Error code: %s\n", strerror(fd));
		return (-1);
	}
	return (fd);
}

/**
 * @brief Close safely the file descriptor
 * Modify the file descriptor to -1 after closing it
 * 
 * @param fd pointer to the file descriptor to close
 * @return int 0 OK, -1 if an error occurred
 */
int	safe_close(int *fd)
{
	int	ret;

	if (fd == NULL)
		return (-1);
	if (*fd < 0)
		return (0);
	ret = close(*fd);
	if (ret < 0)
	{
		ret = errno;
		ft_dprintf(2, RED "Error" RESET "\nFailed to close fd '%d'\n", *fd);
		ft_dprintf(2, "Error code: %s\n", strerror(ret));
		return (-1);
	}
	*fd = -1;
	return (0);
}
