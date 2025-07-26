/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raoul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 15:44:29 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Raoul's includes
#include "cub3d.h"
#include "cub3d_render.h"
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>

// TODO: SUPPRIMER CEIL_COLOR ET FLOOR_COLOR
#define CEIL_COLOR 0xff6494ed
#define FLOOR_COLOR 0xffdddddd

t_data		*cub_init(t_data *data, int fd);
int			cub3d_init_render(t_data *data);

// TODO: Needs to use the map stored in t_data->t_map->map
// Needs to check data structure for validity
int	cub3d_init_render(t_data *data)
{
	int		fd;

	fd = open("testmap.cub", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	if (cub_init(data, fd) == NULL)
	{
		close(fd);
		ft_dprintf(2, "Map error\n");
		return (1);
	}
	close(fd);
	data->input = (t_input){0};
	data->player.pos.x = 10.f;
	data->player.pos.y = 8.5f;
	data->player.angle = -0.66f;
	data->player.fov = (float)(PI) / 2.0f;
	data->map.textures.ceiling.argb = data->map.textures.ceiling.argb;
	data->map.textures.floor.argb = data->map.textures.floor.argb;
	cub_loop(data);
	return (0);
}
