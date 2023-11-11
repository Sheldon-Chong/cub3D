/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:34:32 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/12 00:34:58 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_img *image, t_xy start, t_xy wh, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < wh.y)
	{
		x = -1;
		while (++x < wh.x)
		{
			if (x + start.x > 0 && x + start.x < image->line_length && y
				+ start.y < S_HEIGHT - 2 && y + start.y > 0)
				place_pixel(image, x + start.x, y + start.y, color);
			if (y + start.y > S_HEIGHT || start.x + x > S_WIDTH)
				break ;
		}
	}
}

t_xy	draw_line(t_img *img, t_xy start, double direction, double distance)
{
	double	step;
	double	t;
	int		color;

	step = 0.1;
	t = 0;
	color = rgb(200, 200, 200);
	while (t <= distance)
	{
		if (color > 0)
			put_pixel(img, start.x + t * cos(direction), start.y + t
				* sin(direction), color);
		t += step;
	}
	return ((t_xy){start.x + distance * cos(direction), start.y + distance
		* sin(direction)});
}
