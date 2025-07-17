/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/17 11:50:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>

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

int	main(int argc, char **argv)
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
}
