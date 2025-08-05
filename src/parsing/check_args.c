/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:20:33 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/05 16:35:47 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

static int	read_arguments(int argc, char **argv, t_args *args)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--generate") == 0
			|| ft_strcmp(argv[i], "-g") == 0)
		{
			i++;
			if (i >= argc || argv[i] == NULL)
				return (1);
			args->gen = argv[i];
		}
		else
		{
			if (args->map)
				return (2);
			args->map = argv[i];
		}
		i++;
	}
	return (0);
}

static int	display_error(int err)
{
	if (err == 1)
		ft_dprintf(2, RED "Error" RESET
			"\nPlease specify a map generation size\n");
	else if (err == 2)
		ft_dprintf(2, RED "Error" RESET "\nDuplicate argument\n");
	else if (err == 3)
		ft_dprintf(2, RED "Error" RESET "\nNot a .cub file\n");
	else if (err == 4)
		ft_dprintf(2, RED "Error" RESET "\nNo map given\n");
	return (-1);
}

static int	is_valid_map(char *str)
{
	int		len;

	if (str == NULL)
		return (display_error(4));
	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".cub", 5))
		return (display_error(3));
	return (1);
}

int	check_args(int argc, char **argv, t_args *args)
{
	int	err;

	args->gen = NULL;
	args->map = NULL;
	err = read_arguments(argc, argv, args);
	if (err)
		return (display_error(err));
	return (is_valid_map(args->map));
}
