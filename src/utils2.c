/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:01:58 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/16 22:43:45 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_xy	angle_to_vector(double angle)
{
	return ((t_xy){(cos(angle)), (sin(angle))});
}

double	deg2rad(double num)
{
	return ((M_PI / 180) * num);
}

t_xy	op(t_xy xy1, t_xy xy2, char op)
{
	if (op == '*')
		return ((t_xy){xy1.x * xy2.x, xy1.y * xy2.y});
	if (op == '+')
		return ((t_xy){xy1.x + xy2.x, xy1.y + xy2.y});
	if (op == 'i')
		return ((t_xy){(int)xy1.x, (int)xy1.y});
	return ((t_xy){0, 0});
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_img *image, t_xy start, t_xy wh, int color)
{
	int y = -1;
	int x;

	while (++y < wh.y)
	{
		x = -1;
		while (++x < wh.x)
		{
			if (x + start.x > 0 && x + start.x < image->line_length && y
				+ start.y < SCREEN_HEIGHT - 2 && y + start.y > 0)
				my_mlx_pixel_put(image, x + start.x, y + start.y, color);
			if (y + start.y > SCREEN_HEIGHT || start.x + x > SCREEN_WIDTH)
				break ;
		}
	}
}