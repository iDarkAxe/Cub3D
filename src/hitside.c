/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitside.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/11 18:49:18 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"

t_img	*hitside_texture(t_textures *tex, int hitside, const t_pos2 *step)
{
	if (hitside)
	{
		if (step->y < 0)
			return (&tex->south);
		else
			return (&tex->north);
	}
	else
	{
		if (step->x < 0)
			return (&tex->west);
		else
			return (&tex->east);
	}
}
