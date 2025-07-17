/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raoul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/17 16:42:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Raoul's includes
#include "cubtest.h"
#include "ft_printf.h"
#include "libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>

// TODO SUPPRIMER CEIL_COLOR ET FLOOR_COLOR
#define CEIL_COLOR 0xff6494ed
#define FLOOR_COLOR 0xffdddddd

static int	check_args_open(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <.cub file>\n", argv[0]);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

int	cub3d_raoul(int argc, char **argv)
{
	t_cub	*cub;
	int		fd;

	fd = check_args_open(argc, argv);
	if (fd < 0)
		return (1);
	cub = cub_init(fd);
	close(fd);
	if (cub == NULL)
	{
		ft_dprintf(2, "Map error\n");
		return (1);
	}
	cub->player.pos.x = 2.f;
	cub->player.pos.y = 1.5f;
	cub->player.angle = -0.66f;
	cub->player.fov = PI / 2.0f;
	cub->ceil_color = CEIL_COLOR;
	cub->floor_color = FLOOR_COLOR;
	cub_loop(cub);
	cub_free(cub);
	return (0);
}
