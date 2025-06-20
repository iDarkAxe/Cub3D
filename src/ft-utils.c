/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:43:15 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 16:44:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"
#include "ft_print.h"
#include <string.h>
#include <errno.h>

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
		ft_dprintf(2, RED"Error"RESET"\nRead fd %d: %s\n", fd, strerror(errno));
		safe_close(&fd);
		return (0);
	}
	fd = safe_close(&fd);
	if (fd != 0)
		return (0);
	return (1);
}
