/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:04:27 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/11 08:35:28 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_print.h"
#include "libft.h"

int	cub_args_validation(t_args *args);
int	cub_arg_display_error(int err);

static int	set_option(int argc, char **argv, char **setting,
	int err_if_missing)
{
	if (argc < 2)
		return (err_if_missing);
	if (*setting)
		return (ARGS_DUPLICATE);
	*setting = argv[1];
	return (0);
}

static int	read_option(int argc, char **argv, t_args *args, char *arg)
{
	if (ft_strcmp("--generate", arg) == 0 || ft_strcmp("-g", arg) == 0)
		return (set_option(argc, argv, &args->gen, ARGS_MISSING_GEN));
	if (ft_strcmp("--key", arg) == 0 || ft_strcmp("-k", arg) == 0)
		return (set_option(argc, argv, &args->key_tex, ARGS_MISSING_KEY));
	if (ft_strcmp("--door", arg) == 0 || ft_strcmp("-d", arg) == 0)
		return (set_option(argc, argv, &args->door_tex, ARGS_MISSING_DOOR));
	return (ARGS_UNRECOGNIZED);
}

static int	store_map(char *map, char **dst)
{
	if (*dst)
		return (ARGS_DUPLICATE);
	*dst = map;
	return (0);
}

int	cub_read_args(int argc, char **argv, t_args *args)
{
	int	i;
	int	r;

	i = 1;
	r = 0;
	ft_memset(args, 0, sizeof(t_args));
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			r = read_option(argc - i, &argv[i], args, argv[i]);
			if (r == 0)
				i++;
		}
		else
			r = store_map(argv[i], &args->map);
		if (r != 0)
			return (cub_arg_display_error(r));
		i++;
	}
	return (cub_args_validation(args));
}
