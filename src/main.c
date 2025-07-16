/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:35 by rdesprez          #+#    #+#             */
/*   Updated: 2025/06/21 11:48:19 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <fcntl.h>
#include "libft.h"
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/X.h>

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
	cub_loop(cub);
	cub_free(cub);
}
