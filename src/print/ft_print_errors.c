/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 16:22:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"
#include "ft_print.h"
#include "data_structure.h"

void	print_map_error(t_map *map, enum e_map_error error)
{
	if (!map)
		return ;
	map->error = 1;
	ft_free_file(map);
	if (error == CONFIG_TOO_MANY_PARAMETERS)
		ft_dprintf(2,
			RED "Error" RESET "\nConfig should have only 6 parameters\n");
	else if (error == CONFIG_ALREADY_STORED)
		ft_dprintf(2,
			RED "Error" RESET "\nConfig member is already filled in\n");
	else if (error == CONFIG_MISSING_PARAMETERS)
		ft_dprintf(2,
			RED "Error" RESET "\nAt least one parameter is missing\n");
}

int	print_error(t_map *map, enum e_fx_error error)
{
	if (!map)
		return (2);
	if (error == CHECK_ARGS)
		ft_dprintf(2, RED "Error" RESET "\nAt check_args\n");
	else if (error == FT_MAP_CHECK)
		ft_dprintf(2, RED "Error" RESET "\nAt ft_map_check\n");
	ft_free_file(map);
	return (1);
}
