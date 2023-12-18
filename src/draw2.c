/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 03:06:12 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/18 18:52:43 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_var *var, double pos_x, double pos_y)
{
	if (var->map.map[(int)pos_y][(int)pos_x] == '1')
		draw_rect(&var->minimap, (t_xy){pos_x * MMAP_SIZE, pos_y * MMAP_SIZE},
			(t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(0, 0, 0));
	if (var->map.map[(int)pos_y][(int)pos_x] == 'D')
		draw_rect(&var->minimap, (t_xy){pos_x * MMAP_SIZE, pos_y * MMAP_SIZE},
			(t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(255, 255, 30));
	if (var->map.map[(int)pos_y][(int)pos_x] == 'd')
		draw_rect(&var->minimap, (t_xy){pos_x * MMAP_SIZE, pos_y * MMAP_SIZE},
			(t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(0, 255, 0));
}

void	draw_rect2(t_var *var, t_xy start, t_rc ray, int y)
{
	float	height;

	height = (S_HEIGHT / ((ray.length)));
	draw_rect(&var->screen, (t_xy){start.x, start.y}, (t_xy){1, (height * (1
				/ (double)var->h))}, get_color(ray.texture, var->w
			- ray.texture_column - 1, y));
}

void	draw_rect3(t_var *var, double height, int x, int y)
{
	t_xy	start;

	start = (t_xy){x, ((S_HEIGHT - height)) / 2 + (height * ((double)y
				/ var->h))};
	draw_rect(&var->screen, (t_xy){start.x, start.y}, (t_xy){1, height},
		rgb(100, 100, 100));
}

t_xy	get_start(int x, double height, int y, t_var *var)
{
	return ((t_xy){x, ((S_HEIGHT - height)) / 2 + (height * ((double)y
				/ var->h))});
}
