/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:18:36 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/29 17:27:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mouse.h"

void	ft_mouse_hide(t_data *data)
{
	t_xvar		*var;
	t_win_list	*win;

	if (!data || !data->mlx.mlx_ptr || !data->mlx.win_ptr)
		return ;
	var = (t_xvar *)data->mlx.mlx_ptr;
	win = (t_win_list *)data->mlx.win_ptr;
	XFixesHideCursor(var->display, win->window);
}

void	ft_mouse_show(t_data *data)
{
	t_xvar		*var;
	t_win_list	*win;

	if (!data || !data->mlx.mlx_ptr || !data->mlx.win_ptr)
		return ;
	var = (t_xvar *)data->mlx.mlx_ptr;
	win = (t_win_list *)data->mlx.win_ptr;
	XFixesShowCursor(var->display, win->window);
}
