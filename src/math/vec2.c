/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:38:30 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 15:41:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include <math.h>

t_vec2	vec2rotate(t_vec2 vec, float angle)
{
	t_vec2	res;

	res.x = vec.x * (float)(cos(angle)) - (float)(sin(angle)) *vec.y;
	res.y = vec.x * (float)(sin(angle)) + (float)(cos(angle)) *vec.y;
	return (res);
}
