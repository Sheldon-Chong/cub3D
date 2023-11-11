/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:03:24 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/12 00:36:16 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fire(t_var *var)
{
	if (var->fire)
		var->frame_num++;
	if (var->frame_num > 6)
	{
		var->frame_num = 0;
		var->fire = 0;
	}
}

int	detect_walls(t_var *var, t_rc *rc)
{
	if (var->map.map[(int)rc->curr_cell.y]
		[(int)rc->curr_cell.x] == '1'
		|| var->map.map[(int)rc->curr_cell.y]
		[(int)rc->curr_cell.x] == 'D'
		|| var->map.map[(int)rc->curr_cell.y]
		[(int)rc->curr_cell.x] == 'd')
		return (1);
	return (0);
}

int	detect_doors(t_var *var, t_rc *rc)
{
	if (var->map.map[(int)rc->curr_cell.y]
		[(int)rc->curr_cell.x] == 'D'
		|| var->map.map[(int)rc->curr_cell.y]
		[(int)rc->curr_cell.x] == 'd')
		return (1);
	return (0);
}

void	set_texture(t_rc *rc, t_xy end_pos, t_var *var)
{
	if (detect_doors(var, rc) == 1)
		set_door_tex(rc, end_pos, var,
			var->map.map[(int)rc->curr_cell.y][(int)rc->curr_cell.x]);
	else
	{
		if (rc->xy == 0)
			set_ray_textures("SN"[(rc->dir.y) > 0], rc, end_pos, var);
		if (rc->xy == 1)
			set_ray_textures("WE"[(rc->dir.x) > 0], rc, end_pos, var);
	}
}
