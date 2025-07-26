/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:43:15 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 11:59:40 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include <errno.h>
#include <string.h>

int	try_to_open_close_file(char *file_name)
{
	int	fd;

	if (file_name == NULL)
		return (0);
	fd = safe_open(file_name);
	if (fd < 0)
		return (0);
	if (read(fd, NULL, 0) < 0)
	{
		ft_dprintf(2, RED "Error" RESET "\nRead fd %d: %s\n", fd,
			strerror(errno));
		safe_close(&fd);
		return (0);
	}
	fd = safe_close(&fd);
	if (fd != 0)
		return (0);
	return (1);
}

size_t	count_array_length(char **array)
{
	size_t	index;

	if (array == NULL)
		return (0);
	index = 0;
	while (array[index] != NULL)
		index++;
	return (index);
}
