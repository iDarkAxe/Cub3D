/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/29 15:15:20 by rdesprez         ###   ########.fr       */
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
#include "maze.h"
#include "mlx.h"
#include "maze.h"

static int	try_place_objects(t_map_raoul *map, t_args *args)
{
	if (args->door_tex == NULL)
		return (1);
	ft_printf("Placing objects...\n");
	if (cub_spawn_objects(map, args->key_tex != NULL) == 0)
		return (0);
	ft_printf("All done!\n");
	return (1);
}

static int	generate_maze_if_requested(t_data *data, t_args *args)
{
	t_map_raoul	*map;

	map = cub_new_map_from_dimensions(args->gen);
	if (map == NULL)
	{
		ft_free_all(data);
		return (-1);
	}
	ft_free_map(data->map.map);
	data->map.map = map;
	ft_printf("Generating maze...\n");
	if (cub_growing_tree(data->map.map) == 0)
	{
		ft_free_all(data);
		return (0);
	}
	ft_printf("Maze generated!\n");
	if (try_place_objects(data->map.map, args) == 0)
	{
		ft_free_all(data);
		return (0);
	}
	data->mlx.minimap_size.x = data->map.map->width;
	data->mlx.minimap_size.y = data->map.map->height;
	return (0);
}

static void	store_extra_textures(t_data *data, t_args *args)
{
	data->map.textures.door.path = args->door_tex;
	data->map.textures.key.path = args->key_tex;
}

int	cub3d(int argc, char **argv)
{
	t_data	data;
	t_args	args;

	ft_bzero(&data, sizeof(data));
	ft_srand(get_time_ms());
	if (cub_read_args(argc, argv, &args) != 1)
		return (print_error(&data.map, FT_MAP_CHECK));
	data.map = ft_map_check_dimensions(&data.map, args.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CHECK_ARGS));
	data.map = ft_check_config(&data.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CONFIG_ERROR));
	if (args.gen && generate_maze_if_requested(&data, &args) != 0)
		return (-1);
	store_extra_textures(&data, &args);
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
