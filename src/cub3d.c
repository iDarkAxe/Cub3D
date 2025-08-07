/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/05 16:28:36 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "mlx.h"

int	cub3d(int argc, char **argv)
{
	t_data	data;
	t_args	args;

	if (check_args(argc, argv, &args) != 1)
		return (print_error(&data.map, FT_MAP_CHECK));
	data.map = ft_map_check_dimensions(&data.map, args.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CHECK_ARGS));
	data.map.generation = args.gen;
	data.map = ft_check_config(&data.map);
	if (data.map.error != 0)
		return (print_error(&data.map, CONFIG_ERROR));
	if (store_textures_names(&data.map) == NULL)
		return (print_error(&data.map, STORE_TEXTURES_NAMES));
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
