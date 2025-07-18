/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:47:45 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/18 11:53:24 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "libft.h"
#include "mlx.h"
#include <malloc.h>

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

void	*cubmlx_free(t_cubmlx *mlx)
{
	if (mlx->backbuffer.img)
		mlx_destroy_image(mlx->mlx, mlx->backbuffer.img);
	if (mlx->win && mlx->mlx)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
	return (NULL);
}

t_cubmlx	*cubmlx_init(t_cub *cub)
{
	t_cubmlx	*mlx;

	if (cub == NULL)
		return (NULL);
	mlx = ft_calloc(1, sizeof(t_cubmlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (cubmlx_free(mlx));
	mlx->win = mlx_new_window(mlx->mlx, cub->win_size.x, cub->win_size.y,
			"cubtest");
	if (mlx->win == NULL)
		return (cubmlx_free(mlx));
	if (setup_backbuffer(cub, mlx) == 0)
		return (cubmlx_free(mlx));
	return (mlx);
}
