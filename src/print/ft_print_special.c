/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:12:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/21 11:00:47 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

ssize_t	ft_print_position(int x, int y)
{
	return (ft_printf("Pos: x,y(%d, %d)\n", x, y));
}

ssize_t	ft_print_file(t_map *map)
{
	ssize_t	count_printed;
	ssize_t	temp;
	size_t	count;

	if (map == NULL || map->file == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap or map->file is NULL\n");
		return (-1);
	}
	count_printed = 0;
	count = 0;
	while (count < map->file_nb_lines + 1 && map->file[count] != NULL)
	{
		temp = ft_printf("%s", map->file[count]);
		if (temp < 0)
			return (temp);
		count_printed += temp;
		count++;
	}
	temp = ft_printf("\n");
	if (temp < 0)
		return (temp);
	count_printed += temp;
	return (count_printed);
}

ssize_t	ft_print_config(t_map *map)
{
	ssize_t	count_printed;
	ssize_t	temp;
	size_t	count;

	if (map == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap or config is NULL\n");
		return (-1);
	}
	count_printed = 0;
	count = 0;
	while (count < 6 && map->config[count] != NULL)
	{
		temp = ft_printf("%s", map->config[count]);
		if (temp < 0)
			return (temp);
		count_printed += temp;
		count++;
	}
	return (count_printed);
}

ssize_t	ft_print_map(t_map *map)
{
	ssize_t	count_printed;
	ssize_t	temp;
	size_t	count;

	if (map == NULL || map->map == NULL)
	{
		ft_dprintf(2, RED "Error" RESET "\nMap or map->map is NULL\n");
		return (-1);
	}
	count_printed = 0;
	count = 0;
	while (map->map[count] != NULL)
	{
		temp = ft_printf("%s", map->map[count]);
		if (temp < 0)
			return (temp);
		count_printed += temp;
		count++;
	}
	temp = ft_printf("\n");
	if (temp < 0)
		return (temp);
	count_printed += temp;
	return (count_printed);
}
