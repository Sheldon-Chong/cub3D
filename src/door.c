/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:28:48 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/02 14:00:51 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_var *var)
{
	t_xy	door;
	double	dist;

	dist = 0.3;
	door = (t_xy){var->map.pos.x, var->map.pos.y};
	if (var->map.map[(int)door.y][(int)(door.x + dist)] == 'D')
		var->map.map[(int)door.y][(int)(door.x + dist)] = 'd';
	else if (var->map.map[(int)door.y][(int)(door.x - dist)] == 'D')
		var->map.map[(int)door.y][(int)(door.x - dist)] = 'd';
	else if (var->map.map[(int)(door.y + dist)][(int)(door.x)] == 'D')
		var->map.map[(int)(door.y + dist)][(int)(door.x)] = 'd';
	else if (var->map.map[(int)(door.y - dist)][(int)(door.x)] == 'D')
		var->map.map[(int)(door.y - dist)][(int)(door.x)] = 'd';
	
}

void	close_door(t_var *var)
{
	t_xy	door;
	double	dist;

	dist = 0.3;
	if(var->map.map[(int)var->map.pos.y][(int)var->map.pos.x] == 'd')
		return ;
	door = (t_xy){var->map.pos.x, var->map.pos.y};
	if (var->map.map[(int)door.y][(int)(door.x + dist)] == 'd')
		var->map.map[(int)door.y][(int)(door.x + dist)] = 'D';
	else if (var->map.map[(int)door.y][(int)(door.x - dist)] == 'd')
		var->map.map[(int)door.y][(int)(door.x - dist)] = 'D';
	else if (var->map.map[(int)(door.y + dist)][(int)(door.x)] == 'd')
		var->map.map[(int)(door.y + dist)][(int)(door.x)] = 'D';
	else if (var->map.map[(int)(door.y - dist)][(int)(door.x)] == 'd')
		var->map.map[(int)(door.y - dist)][(int)(door.x)] = 'D';
	
}

int	handle_keyrelease(int keycode, t_var *var)
{
	if (keycode == 53)
		exit(0);
	if (keycode == LINUX_X)
		open_door(var);
	if (keycode == 6)
		close_door(var);
	return (0);
}

// void	set_door_close_tex(t_rc *rc, t_xy end_pos, t_var *var)
// {
// 	double dif;

// 	dif = 0;
// 	if (rc->xy == 0)
// 	{
// 		dif = end_pos.x - rc->current_cell.x;
// 		rc->texture = var->tex.door_open;
// 	}
// 	else if (rc->xy == 1)
// 	{
// 		dif = end_pos.y - rc->current_cell.y;
// 		rc->texture = var->tex.door_open;
// 	}
// 	rc->texture_column = (int)(dif * var->w);
// }