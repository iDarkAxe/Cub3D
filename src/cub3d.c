/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 08:56:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "mlx.h"

int		ft_mlx_init(t_mlx *mlx);

void	ft_mlx_end(t_mlx *mlx);

/**
 * @brief Main function of the cub3d project
 *
 * @param argc number of arguments
 * @param argv array of string arguments
 * @return int 0 if the program ends correctly, -1 otherwise
 */
int	cub3d(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 1)
		return (print_error(&data.map, FT_MAP_CHECK));
	data.map = ft_map_check_dimensions(&data.map, argv[1]);
	if (data.map.error != 0)
		return (print_error(&data.map, CHECK_ARGS));
	data.map = ft_check_config(&data.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CONFIG_ERROR));
	if (store_textures_names(&data.map) == NULL)
		return (print_error(&data.map, STORE_TEXTURES_NAMES));
	if (ft_mlx_init(&data.mlx) != 0)
		ft_dprintf(2, "Erreur mlx\n");
	mlx_loop(data.mlx.mlx_ptr);
	ft_mlx_end(&data.mlx);
	ft_free_textures_path(&data.map);
	ft_free_file(&data.map);
	return (0);
}
