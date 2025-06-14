/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/14 15:53:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include <fcntl.h>

t_map	ft_map_check(t_map *map, char *map_name)
{
	int	fd;

	if (map == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap structure is NULL\n");
		return ((t_map){.error = -1});
	}
	ft_bzero(map, sizeof(t_map));
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, RED "Error" RESET "\nFailed to open map file '%s'\n",
			map_name);
		return ((t_map){.error = -1});
	}
	if (close(fd) < 0)
	{
		ft_dprintf(2, RED "Error" RESET "\nFailed to close map file '%s'\n",
			map_name);
		return ((t_map){.error = -1});
	}
	return (*map);
}
