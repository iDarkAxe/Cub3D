/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:52:04 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/17 13:25:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "libft.h"
#include "get_next_line.h"
#include "libft_collections.h"
#include <malloc.h>
#include <unistd.h>

static int	push_line(t_ptrvec *vec, int fd)
{
	char	*line;
	int		i;
	int		n;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0')
			n = 0;
		else
			n = 1;
		if (ptrvecpush(vec, (void *)(long)n) == 0)
			return (-1);
		i++;
	}
	free(line);
	return (i);
}

static int	get_walls(t_map *map, t_ptrvec *vec, int fd)
{
	int	i;
	int	flag;

	flag = push_line(vec, fd);
	if (flag < 0)
		return (0);
	map->width = flag;
	i = 1;
	while (flag)
	{
		flag = push_line(vec, fd);
		if (flag == 0)
			break ;
		if (flag == -1 || flag != (int)map->width)
			return (0);
		i++;
	}
	map->height = i;
	return (1);
}

static t_map	*map_finalize(t_map *map, t_ptrvec *vec)
{
	int		*tab;
	size_t	i;

	tab = malloc(sizeof(int) * vec->len);
	if (tab == NULL)
	{
		free(map);
		ptrvecfree(vec, NULL);
		return (NULL);
	}
	i = 0;
	while (i < vec->len)
	{
		tab[i] = (int)(long)vec->data[i];
		i++;
	}
	map->walls = tab;
	ptrvecfree(vec, NULL);
	return (map);
}

t_map	*parse_map(int fd)
{
	t_map		*map;
	t_ptrvec	*vec;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	vec = ptrvecnew(16);
	if (vec == NULL)
	{
		free(map);
		return (NULL);
	}
	if (get_walls(map, vec, fd) == 0)
	{
		free(map);
		ptrvecfree(vec, NULL);
		return (NULL);
	}
	return (map_finalize(map, vec));
}
