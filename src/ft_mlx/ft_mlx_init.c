/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:47:45 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 15:44:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include "libft.h"
#include "mlx.h"
#include <malloc.h>

// TODO: Remove as ft_mlx_end does the same
// void	*cubmlx_free(t_cubmlx *mlx)
// {
// 	if (mlx->backbuffer.img)
// 		mlx_destroy_image(mlx->mlx, mlx->backbuffer.img);
// 	if (mlx->win && mlx->mlx)
// 		mlx_destroy_window(mlx->mlx, mlx->win);
// 	if (mlx->mlx)
// 	{
// 		mlx_destroy_display(mlx->mlx);
// 		free(mlx->mlx);
// 	}
// 	free(mlx);
// 	return (NULL);
// }
