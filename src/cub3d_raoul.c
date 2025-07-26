/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raoul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 16:44:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Raoul's includes
#include "cub3d.h"
#include "cub3d_render.h"
#include "ft_printf.h"
#include "ft_print.h"
#include "mlx.h"
#include <fcntl.h>
#include <stdio.h>

int	cub3d_init_render(t_data *data)
{
	int		fd;

	if (!data)
		return (print_error(NULL, CUB_INIT_RENDER));
	fd = open("testmap.cub", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	if (cub_init(data, fd) == NULL)
	{
		close(fd);
		return (print_error(&data->map, CUB_INIT));
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
