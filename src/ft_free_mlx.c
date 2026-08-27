/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/11 10:20:31 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

void	ft_mlx_end(t_mlx *mlx)
{
	if (!mlx || !mlx->mlx_ptr)
		return;
	if (mlx->z_buffer)
		free(mlx->z_buffer);
	if (mlx->backbuffer.img)
	{
		mlx_delete_image(mlx->mlx_ptr, mlx->backbuffer.img);
		mlx->backbuffer.img = NULL;
	}
	if (mlx->win_ptr != NULL)
	{
		mlx_delete_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	if (mlx->mlx_ptr != NULL)
	{
		mlx_terminate(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
	}
}

void	ft_free_settings(t_mlx *mlx)
{
	if (!mlx || !mlx->mlx_ptr)
		return;
	if (mlx->settings.background.img)
	{
		mlx_delete_image(mlx->mlx_ptr, mlx->settings.background.img);
		mlx->settings.background.img = NULL;
	}
	if (mlx->settings.circle_no.img)
	{
		mlx_delete_image(mlx->mlx_ptr, mlx->settings.circle_no.img);
		mlx->settings.circle_no.img = NULL;
	}
	if (mlx->settings.circle_yes.img)
	{
		mlx_delete_image(mlx->mlx_ptr, mlx->settings.circle_yes.img);
		mlx->settings.circle_yes.img = NULL;
	}
	if (mlx->settings.win_ptr)
	{
		mlx_delete_window(mlx->mlx_ptr, mlx->settings.win_ptr);
		mlx->settings.win_ptr = NULL;
	}
}
