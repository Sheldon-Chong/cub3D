/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:01:58 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/02 14:09:59 by shechong         ###   ########.fr       */
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

int	rgb(int r, int g, int b)
{
	return (0xFFFFFF & (r << 16 | g << 8 | b));
}

void	set_door_tex(t_rc *rc, t_xy end_pos, t_var *var, char door)
{
	double dif;

	dif = 0;
	if(door == 'D')
		rc->texture = var->tex.door;
	else if(door == 'd')
		rc->texture = var->tex.door_open;
	if (rc->xy == 0)
		dif = end_pos.x - rc->current_cell.x;
	else if (rc->xy == 1)
		dif = end_pos.y - rc->current_cell.y;
	rc->texture_column = (int)(dif * var->w);
}