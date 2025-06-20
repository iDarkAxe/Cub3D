/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:12:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 16:23:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"

size_t	is_config_line(char *line)
{
	static char	*config_str[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", NULL};
	size_t		i;

	i = 0;
	while (config_str[i])
	{
		if (ft_strncmp(line, config_str[i], ft_strlen(config_str[i])) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

char	**fill_config_region(t_map *map)
{
	size_t	index;
	size_t	ret;
	int		nbr_config;

	if (!map || !map->file)
		return (NULL);
	index = 0;
	nbr_config = 0;
	while (map->error == 0 && map->file[index])
	{
		ret = is_config_line(map->file[index]);
		if (ret != 0 && ret > 0 && map->config[ret - 1] != NULL)
			print_map_error(map, CONFIG_ALREADY_STORED);
		if (map->error == 0 && ret != 0 && ret > 0)
		{
			map->config[ret - 1] = map->file[index];
			nbr_config++;
		}
		if (nbr_config > 6)
			print_map_error(map, CONFIG_TOO_MANY_PARAMETERS);
		index++;
	}
	if (nbr_config != 6)
		print_map_error(map, CONFIG_MISSING_PARAMETERS);
	return (map->config);
}
