/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:43:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 17:04:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_print.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	safe_open(char *file_name);
int	safe_close(int *fd);

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
		ft_dprintf(2, RED "Code:" RESET " %s\n", strerror(fd));
		return (-1);
	}
	return (fd);
}

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
		ft_dprintf(2, RED "Code:" RESET " %s\n", strerror(ret));
		return (-1);
	}
	*fd = -1;
	return (0);
}
