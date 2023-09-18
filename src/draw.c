/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:45:20 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/18 15:56:18 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_color(int t, int *clr)
{
	int	r;
	int	g;
	int	b;

	r = clr[0];
	g = clr[1];
	b = clr[2];
	return (t << 24 | r << 16 | g << 8 | b);
}

void	set_tex(t_vars *var, t_img img)
{
	if (var->rc.side == 0)
		var->rc.wall_x = var->rc.pos_y + var->rc.perp_wall * var->rc.ray_y;
	else
		var->rc.wall_x = var->rc.pos_x + var->rc.perp_wall * var->rc.ray_y;
	var->rc.wall_x -= floor(var->rc.wall_x);
	var->rc.tex_x = (int)(var->rc.wall_x * img.width);
	if ((var->rc.side == 0 && var->rc.ray_x > 0) || (var->rc.side == 1
			&& var->rc.ray_x < 0))
		var->rc.tex_x = img.width - var->rc.tex_x;
	var->rc.tex_y = 0;
	var->rc.tex_y_step = img.height / (double)var->rc.line_height;
	if (var->rc.line_height > var->max_height)
	{
		var->rc.tex_y = (int)(var->rc.line_height - var->max_height)
			* var->rc.tex_y_step / 2;
	}
}

void	background(t_vars *var)
{
	int	x;
	int	y;

	x = 0;
	while (x < var->max_width)
	{
		y = 0;
		if (y < var->max_height)
		{
			if (y < var->max_height / 2)
				pix_draw(var, x, y, create_color(0, var->rc.rgb_c));
			else
				pix_draw(var, x, y, create_color(0, var->rc.rgb_f));
			y++;
		}
		++x;
	}
}

void	draw_texture(t_vars *var, t_img img, int x)
{
	char	*dst;
	int		wall_y;
	int		color;

	set_tex(var, img);
	wall_y = var->rc.start;
	while (wall_y <= var->rc.end)
	{
		dst = img.addr + ((int)(var->rc.tex_y) % img.height * img.line_length
				+ var->rc.tex_x % img.width * (img.bpp / 8));
		color = *(unsigned int *)dst;
		put_pix(&var->screen, x, wall_y, color);
		wall_y++;
		var->rc.tex_y += var->rc.tex_y_step;
	}
}

void	draw_img(t_vars *var)
{
	int	x;

	background(var);
	set_img(var);
	x = 0;
	while (x < var->max_width)
	{
		ray_pos(var, x);
		ray_len(&var->rc);
		dda(var);
		set_projection(var);
		if (var->rc.side == 0 && var->rc.step_x == 1)
			draw_texture(var, var->tex_img.n, x);
		if (var->rc.side == 0 && var->rc.step_x == -1)
			draw_texture(var, var->tex_img.s, x);
		if (var->rc.side == 1 && var->rc.step_x == 1)
			draw_texture(var, var->tex_img.e, x);
		if (var->rc.side == 1 && var->rc.step_x == -1)
			draw_texture(var, var->tex_img.w, x);
		x++;
	}
}
