/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:05:29 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/18 15:56:18 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_pos(t_vars *var, int x)
{
	var->rc.cam_x = 2 * x / (double)var->max_width - 1;
	var->rc.ray_x = var->rc.dir_x + var->rc.plane_x * var->rc.cam_x;
	var->rc.ray_y = var->rc.dir_y + var->rc.plane_y * var->rc.cam_x;
	var->rc.map_x = (int)var->rc.pos_x;
	var->rc.map_y = (int)var->rc.pos_y;
}

void	ray_len(t_raycast *rc)
{
	rc->d_dst_x = fabs(1 / rc->ray_x);
	rc->d_dst_y = fabs(1 / rc->ray_y);
	rc->hit = 0;
	if (rc->ray_x < 0)
	{
		rc->step_x = -1;
		rc->side_dst_x = (rc->pos_x - rc->map_x) * rc->d_dst_y;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dst_x = (rc->map_x + 1.0 - rc->pos_x) * rc->d_dst_y;
	}
	if (rc->ray_y < 0)
	{
		rc->step_y = -1;
		rc->side_dst_y = (rc->pos_y - rc->map_y) * rc->d_dst_x;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dst_y = (rc->map_y + 1.0 - rc->pos_y) * rc->d_dst_x;
	}
}

void	dda(t_vars *var)
{
	while (var->rc.hit == 0)
	{
		if (var->rc.side_dst_x < var->rc.side_dst_y)
		{
			var->rc.side_dst_x += var->rc.d_dst_y;
			var->rc.map_x += var->rc.step_x;
			var->rc.side = 0;
		}
		else
		{
			var->rc.side_dst_y += var->rc.d_dst_x;
			var->rc.map_y += var->rc.step_y;
			var->rc.side = 1;
		}
		if (var->map.map[var->rc.map_y][var->rc.map_x] == '1')
			var->rc.hit = 1;
	}
}

void	set_projection(t_vars *var)
{
	if (var->rc.side == 0)
	{
		var->rc.perp_wall = (var->rc.map_x - var->rc.pos_x + (1
					- var->rc.step_x) / 2) / var->rc.ray_x;
	}
	else
	{
		var->rc.perp_wall = (var->rc.map_y - var->rc.pos_y + (1
					- var->rc.step_y) / 2) / var->rc.ray_y;
	}
	var->rc.line_height = (int)(var->max_height / var->rc.perp_wall);
	var->rc.start = -var->rc.line_height / 2 + var->max_height / 2;
	if (var->rc.start < 0)
		var->rc.start = 0;
	var->rc.end = var->rc.line_height / 2 + var->max_height / 2;
	if (var->rc.end >= var->max_height)
		var->rc.end = var->max_height - 1;
}
