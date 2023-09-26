/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:23:04 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/26 23:37:08 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_start(t_var *var, int x)
{
	int	y;

	y = var->rc.start;
	while (y < var->rc.end)
	{
		// insert pixel putting method here
		var->rc.texY += var->rc.stepY;
		y++;
	}
}

void	draw_tex(t_var *var, int x)
{
	if (var->rc.side == 1)
		var->rc.wallX = var->map.loc_x + var->rc.perp_dist * var->rc.rayX;
	else
		var->rc.wallX = var->map.loc_y + var->rc.perp_dist * var->rc.rayY;
	var->rc.wallX -= floor(var->rc.wallX);
	var->rc.texX = (int)(var->rc.wallX * (double)var->w);
	if ((var->rc.side == 0 && var->rc.rayX > 0) || (var->rc.side == 1
			&& var->rc.rayY < 0))
		var->rc.texX = var->w - var->rc.texX - 1;
	var->rc.step = var->h / var->rc.line_height;
	var->rc.texPos = (var->rc.start - (var->max_h * 0.5) + (var->rc.line_height
			* 0.5) * var->rc.step);
	draw_start(t_var * var, int x);
}