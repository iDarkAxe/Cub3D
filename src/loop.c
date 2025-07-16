/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:36:48 by rdesprez          #+#    #+#             */
/*   Updated: 2025/06/25 14:12:58 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "mlx.h"
#include <X11/X.h>
#include <math.h>

static void	set_key(int keycode, t_input *input, int set)
{
	if (keycode == 'w')
		input->fwd = set;
	else if (keycode == 's')
		input->bckwd = set;
	else if (keycode == 'a')
		input->left = set;
	else if (keycode == 'd')
		input->right = set;
}

static int	cub_keydown_hook(int keycode, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	set_key(keycode, input, 1);
	return (0);
}

static int	cub_keyup_hook(int keycode, void *param)
{
	t_input	*input;

	input = (t_input *)param;
	set_key(keycode, input, 0);
	return (0);
}

static int	loop_hook(void	*param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->input.fwd)
	{
		cub->player.pos.x += 0.01f * cos(cub->player.angle);
		cub->player.pos.y += 0.01f * sin(cub->player.angle);
	}
	if (cub->input.bckwd)
	{
		cub->player.pos.x -= 0.01f * cos(cub->player.angle);
		cub->player.pos.y -= 0.01f * sin(cub->player.angle);
	}
	if (cub->input.left)
		cub->player.angle -= 0.01f;
	if (cub->input.right)
		cub->player.angle += 0.01f;
	if (cub->player.angle >= (2.f * PI))
		cub->player.angle -= (2.f * PI);
	if (cub->player.angle < 0.f)
		cub->player.angle += (2.f * PI);
	cub_render(cub);
	return (1);
}

void	cub_loop(t_cub *cub)
{
	mlx_hook(cub->mlx->win, DestroyNotify, StructureNotifyMask, &mlx_loop_end,
		cub->mlx->mlx);
	mlx_hook(cub->mlx->win, KeyPress, KeyPressMask, &cub_keydown_hook,
		&cub->input);
	mlx_hook(cub->mlx->win, KeyRelease, KeyReleaseMask, &cub_keyup_hook,
		&cub->input);
	mlx_loop_hook(cub->mlx->mlx, &loop_hook, cub);
	mlx_loop(cub->mlx->mlx);
}
