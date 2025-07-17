/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:20:33 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/21 11:23:40 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_printf.h"

int			check_args(int argc, char **argv);
static int	check_map_name(char *map_name);

int	check_args(int argc, char **argv)
{
	if (argc < 2 || !argv || !argv[0] || !argv[1])
	{
		ft_dprintf(2, RED "Error" RESET "\nNo map file provided\n");
		ft_dprintf(2, "Usage: %s <map_name>.cub\n", argv[0]);
		return (-1);
	}
	if (argv[2] != NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nToo many arguments\n");
		return (-1);
	}
	if (check_map_name(argv[1]) != 1)
	{
		ft_dprintf(2, RED "Error" RESET "\nInvalid map file name\n");
		return (-1);
	}
	return (1);
}

int	check_map_name(char *map_name)
{
	size_t	len;

	if (map_name == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap file name is NULL\n");
		return (-1);
	}
	len = ft_strlen(map_name);
	if (len < 5)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap file name too short\n");
		ft_dprintf(2, "Name must be at least 5 characters long : <name>.cub\n");
		return (-1);
	}
	if (ft_strnstr(map_name, ".cub", len) == NULL || ft_strncmp(&map_name[len
				- 4], ".cub", 4) != 0)
	{
		ft_dprintf(2,
			RED "Error" RESET "\nMap file name must end with '.cub'\n");
		ft_dprintf(2, "Name must be at least 5 characters long : <name>.cub\n");
		return (-1);
	}
	return (1);
}
