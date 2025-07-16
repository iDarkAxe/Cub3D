/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:27:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/06/21 11:51:00 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "libft.h"
#include <stdlib.h>

void	cub_free(t_cub *cub)
{
	if (cub->mlx)
		cubmlx_free(cub->mlx);
	if (cub->map)
	{
		free(cub->map->walls);
		free(cub->map);
	}
	free(cub);
}

t_cub	*cub_init(int fd)
{
	t_map	*map;
	t_cub	*cub;

	map = parse_map(fd);
	if (map == NULL)
		return (NULL);
	cub = ft_calloc(1, sizeof(t_cub));
	if (cub == NULL)
	{
		free(map->walls);
		free(map);
		return (NULL);
	}
	cub->map = map;
	cub->mlx = cubmlx_init();
	if (cub->mlx == NULL)
	{
		cub_free(cub);
		return (NULL);
	}
	return (cub);
}
