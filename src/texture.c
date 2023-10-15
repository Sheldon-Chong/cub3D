/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:23:04 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/16 00:17:39 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && y > 0 && x < 1920 && y < 1080)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)pixel = color;
	}
}

// void	draw_start(t_var *var, int x)
// {
// 	int	y;

// 	(void)x;
// 	y = var->rc.start;
// 	while (y < var->rc.end)
// 	{
// 		// if (var->map.dir == 'N')
// 		// 	put_pixel(var->tex.n, x, y);
// 		var->rc.tex_y += var->rc.step_y;
// 		y++;
// 	}
// }

// void	draw_tex(t_var *var, int x)
// {
// 	if (var->rc.side == 1)
// 		var->rc.wall = var->map.loc_x + var->rc.perp_dist * var->rc.ray_x;
// 	else
// 		var->rc.wall = var->map.loc_y + var->rc.perp_dist * var->rc.ray_y;
// 	var->rc.wall -= floor(var->rc.wall);
// 	var->rc.tex_x = (int)(var->rc.wall * (double)var->w);
// 	if ((var->rc.side == 0 && var->rc.ray_x > 0) || (var->rc.side == 1
// 			&& var->rc.ray_y < 0))
// 		var->rc.tex_x = var->w - var->rc.tex_x - 1;
// 	var->rc.step = var->h / var->rc.line_height;
// 	var->rc.tex_pos = (var->rc.start - (var->max_h * 0.5) + (var->rc.line_height
// 				* 0.5) * var->rc.step);
// 	draw_start(var, x);
// }
