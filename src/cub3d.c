/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/08 16:26:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 ******************************************************************************
 * @file           : cub3d.c
 * @brief          : Main program of the Cub3D
 ******************************************************************************
 * @date 08 August 2025
 * @mainpage Cub3D
 * @section Introduction
 *
 * Game using Wolfenstein3D technique for rendering.
 * A lot of features like collisions, minimap and FOV !
 * See README.md for the whole presentation and walkthrough.
 *
 ******************************************************************************
 */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "mlx.h"
#include "maze.h"

int	generate_maze_if_requested(t_data *data, char *gen);

int	cub3d(int argc, char **argv)
{
	t_data	data;
	t_args	args;

	ft_bzero(&data, sizeof(data));
	ft_srand(get_time_ms());
	if (check_args(argc, argv, &args) != 1)
		return (print_error(&data.map, FT_MAP_CHECK));
	data.map = ft_map_check_dimensions(&data.map, args.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CHECK_ARGS));
	data.map = ft_check_config(&data.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CONFIG_ERROR));
	if (args.gen && generate_maze_if_requested(&data, args.gen) != 0)
		return (-1);
	if (ft_mlx_init(&data) != 0)
	{
		ft_dprintf(2, "Erreur Init mlx\n");
		ft_free_all(&data);
		return (-1);
	}
	mlx_loop(data.mlx.mlx_ptr);
	ft_free_all(&data);
	return (0);
}
