/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:27:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/23 13:07:02 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cubtest.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

void	cub_free(t_cub *cub)
{
	cubmlx_free(&cub->mlx);
	if (cub->map)
	{
		free(cub->map->walls);
		free(cub->map);
	}
	free(cub);
}

static int	setup_backbuffer(t_cub *cub, t_cubmlx *mlx)
{
	mlx->backbuffer.img = mlx_new_image(mlx->mlx, cub->win_size.x,
			cub->win_size.y);
	if (mlx->backbuffer.img == NULL)
		return (0);
	mlx->backbuffer.pxls = mlx_get_data_addr(mlx->backbuffer.img,
			&mlx->backbuffer.bits_per_pixel, &mlx->backbuffer.width,
			&mlx->backbuffer.endian);
	mlx->backbuffer.height = (cub->win_size.x * cub->win_size.y)
		/ mlx->backbuffer.width;
	return (1);
}

t_cub	*cub_init(t_mlx *mlx, int fd)
{
	t_map_raoul	*map;
	t_cub		*cub;

	map = parse_map(fd);
	if (map == NULL)
		return (NULL);
	cub = ft_calloc(1, sizeof(t_cub));
	if (cub == NULL)
	{
		free(map->walls);
		free(map);
		return (NULL);
	}
	cub->map = map;
	cub->win_size.x = mlx->win_size.x;
	cub->win_size.y = mlx->win_size.y;
	cub->minimap_size.x = cub->map->width * MINIMAP_TILE_SIZE;
	cub->minimap_size.y = cub->map->height * MINIMAP_TILE_SIZE;
	cub->mlx.mlx = mlx->mlx_ptr;
	cub->mlx.win = mlx->win_ptr;
	if (setup_backbuffer(cub, &cub->mlx) == 0)
		return (cubmlx_free(&cub->mlx));
	return (cub);
}
