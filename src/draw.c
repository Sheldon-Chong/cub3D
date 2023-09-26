/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:47:09 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/26 16:47:57 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_steps(t_var *var)
{
	if (var->rc.rayX < 0)
	{
		var->rc.sideX = -1;
		var->rc.stepX = (var->map.loc_x - var->rc.mapX) * var->rc.deltaX;
	}
	else
	{
		var->rc.sideX = 1;
		var->rc.stepX = (var->rc.mapX + 1 - var->map.loc_x) * var->rc.deltaX;
	}
	if (var->rc.rayY < 0)
	{
		var->rc.sideY = -1;
		var->rc.stepY = (var->map.loc_y - var->rc.mapY) * var->rc.deltaY;
	}
	else
	{
		var->rc.sideY = 1;
		var->rc.stepY = (var->rc.mapY + 1 - var->map.loc_y) * var->rc.deltaY;
	}
}

void	dda(t_rc *rc, t_map *map)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->sideX < rc->sideY)
		{
			rc->sideX += rc->deltaX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideY += rc->deltaY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (map->map[rc->mapX][rc->mapY] == 1)
			rc->hit = 1;
	}
}

void	ray_distance(t_rc *rc, t_var *var)
{
	if (rc->side == 0)
		rc->perp_dist = rc->sideX - rc->deltaX;
	else
		rc->perp_dist = rc->sideY - rc->deltaY;
	rc->line_height = (int)(var->max_h / rc->perp_dist);
	rc->start = (-1 * rc->line_height) / 2 + (var->max_h / 2);
	if (rc->start < 0)
		rc->start = 0;
	rc->end = (rc->line_height / 2) + (var->max_h / 2);
	if (rc->end >= var->max_h)
		rc->end = var->max_h - 1;
}

int	draw_img(t_var *var)
{
	int x;

	x = 0;
	while (x < var->max_w)
	{
		var->rc.camX = 2 * x / (double)var->max_w - 1;
		var->rc.rayX = var->rc.dirX + var->rc.planeX * var->rc.camX;
		var->rc.rayY = var->rc.dirY + var->rc.planeY * var->rc.camX;
		var->rc.deltaX = fabs(1 / var->rc.dirX);
		var->rc.deltaY = fabs(1 / var->rc.dirY);
		cal_steps(var);
		dda(&var->rc, &var->map);
		ray_distance(&var->rc, &var);
		draw_tex(&var, x);
		x++;
	}
	return (0);
}