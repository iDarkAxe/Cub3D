/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:20:33 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/11 08:20:27 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	cub_arg_display_error(int err)
{
	if (err == ARGS_MISSING_GEN)
		ft_dprintf(2, RED "Error" RESET
			"\nPlease specify a map generation size\n");
	else if (err == ARGS_DUPLICATE)
		ft_dprintf(2, RED "Error" RESET "\nDuplicate argument\n");
	else if (err == ARGS_NOT_CUB)
		ft_dprintf(2, RED "Error" RESET "\nNot a .cub file\n");
	else if (err == ARGS_NO_MAP)
		ft_dprintf(2, RED "Error" RESET "\nNo map given\n");
	else if (err == ARGS_MAZE_REQUIRED)
		ft_dprintf(2, RED "Error" RESET
			"\nA maze must be generated to be able to spawn a key and/or a"
			"door.\n");
	else if (err == ARGS_DOOR_REQUIRED)
		ft_dprintf(2, RED "Error" RESET
			"\nA door must be generated to be able to spawn a key.\n");
	else if (err == ARGS_MISSING_KEY)
		ft_dprintf(2, RED "Error" RESET "\nPlease specify a key texture.\n");
	else if (err == ARGS_MISSING_DOOR)
		ft_dprintf(2, RED "Error" RESET "\nPlease specify a door texture.\n");
	else if (err == ARGS_UNRECOGNIZED)
		ft_dprintf(2, RED "Error" RESET "\nUnrecognized option\n");
	return (-1);
}

static int	is_valid_map(char *str)
{
	int		len;

	if (str == NULL)
		return (ARGS_NO_MAP);
	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".cub", 5))
		return (ARGS_NOT_CUB);
	return (0);
}

static int	verify_generation_options(t_args *args)
{
	if ((args->door_tex || args->key_tex) && !args->gen)
		return (ARGS_MAZE_REQUIRED);
	if (args->gen && args->key_tex && !args->door_tex)
		return (ARGS_DOOR_REQUIRED);
	return (0);
}

int	cub_args_validation(t_args *args)
{
	int	r;

	r = verify_generation_options(args);
	if (r > 0)
		return (cub_arg_display_error(r));
	r = is_valid_map(args->map);
	if (r > 0)
		return (cub_arg_display_error(r));
	return (1);
}
