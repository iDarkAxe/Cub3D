/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:47:45 by rdesprez          #+#    #+#             */
/*   Updated: 2025/06/18 09:43:16 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <malloc.h>
#include "libft.h"
#include "mlx.h"

static int	setup_backbuffer(t_cubmlx *mlx)
{
	mlx->backbuffer.img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (mlx->backbuffer.img == NULL)
		return (0);
	mlx->backbuffer.pxls = mlx_get_data_addr(mlx->backbuffer.img,
			&mlx->backbuffer.bits_per_pixel,
			&mlx->backbuffer.width,
			&mlx->backbuffer.endian);
	mlx->backbuffer.height = (1280 * 720) / mlx->backbuffer.width;
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

t_cubmlx	*cubmlx_init(void)
{
	t_cubmlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_cubmlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (cubmlx_free(mlx));
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cubtest");
	if (mlx->win == NULL)
		return (cubmlx_free(mlx));
	if (setup_backbuffer(mlx) == 0)
		return (cubmlx_free(mlx));
	return (mlx);
}
