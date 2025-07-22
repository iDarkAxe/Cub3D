/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raoul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/22 15:30:40 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Raoul's includes
#include "cubtest.h"
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>

// TODO SUPPRIMER CEIL_COLOR ET FLOOR_COLOR
#define CEIL_COLOR 0xff6494ed
#define FLOOR_COLOR 0xffdddddd

t_cub	*cub_init(t_mlx *mlx, int fd);

void	free_cub(t_cub *cub)
{
	if (cub == NULL)
		return ;
	if (cub->map)
	{
		free(cub->map->walls);
		free(cub->map);
	}
	if (cub->mlx.backbuffer.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.backbuffer.img);
		cub->mlx.backbuffer.img = NULL;
	}
	free(cub);
	cub = NULL;
}

// TODO: Needs to use the map stored in t_data->t_map->map
int	cub3d_rendu(t_mlx *mlx)
{
	int		fd;
	t_cub	*cub;

	fd = open("testmap.cub", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	cub = cub_init(mlx, fd);
	close(fd);
	if (cub == NULL)
	{
		ft_dprintf(2, "Map error\n");
		return (1);
	}
	cub->player.pos.x = 10.f;
	cub->player.pos.y = 8.5f;
	cub->player.angle = -0.66f;
	cub->player.fov = PI / 2.0f;
	cub->ceil_color = CEIL_COLOR;
	cub->floor_color = FLOOR_COLOR;
	cub_loop(cub);
	free_cub(cub);
	return (0);
}
