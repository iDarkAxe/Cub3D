/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:10:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_keys.h"
#include "mlx.h"
#include "so_long.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Main function of the so_long project
 *
 * @param argc number of arguments
 * @param argv array of string arguments
 * @return int 0 if the program ends correctly, -1 otherwise
 */
int	so_long(int argc, char **argv)
{
	t_map	*map;
	t_mlx	mlx;

	(void)argc;
	map = check_borders(dimensions_verif(argv[1]));
	if (map == NULL || map->map == NULL || map->error == -1)
		return ((void)write(2, "Error\nAt check_borders\n", 23), -1);
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
		return ((void)write(2, "Error\nInit MLX\n", 14), -1);
	if (ft_store_textures(&mlx, map) == NULL)
		return ((void)write(2, "Error\nStore textures\n", 22),
			(void)free_map_textures(&mlx, map), -1);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, map->textures.north.width
			* (int)map->width, map->textures.north.width * ((int)map->height
				+ 1), "So_long");
	if (mlx.win_ptr == NULL)
		return ((void)write(2, "Error\n", 7), (void)ft_exit(mlx, map), -1);
	mlx_hook(mlx.win_ptr, 17, (1L << 17), close_window, (void *)&mlx);
	mlx_hook(mlx.win_ptr, 2, (1L << 0), handle_keypress,
		(void *)&((t_store){&mlx, map}));
	ft_draw_map(&mlx, map);
	mlx_loop(mlx.mlx_ptr);
	return ((void)ft_exit(mlx, map), 0);
}
