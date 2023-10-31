/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:28:48 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/31 18:43:20 by nwai-kea         ###   ########.fr       */
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
		var->map.map[(int)door.y][(int)(door.x + dist)] = '0';
	else if (var->map.map[(int)door.y][(int)(door.x - dist)] == 'D')
		var->map.map[(int)door.y][(int)(door.x - dist)] = '0';
	else if (var->map.map[(int)(door.y + dist)][(int)(door.x)] == 'D')
		var->map.map[(int)(door.y + dist)][(int)(door.x)] = '0';
	else if (var->map.map[(int)(door.y - dist)][(int)(door.x)] == 'D')
		var->map.map[(int)(door.y - dist)][(int)(door.x)] = '0';
	// if (var->map.map[(int)door.y][(int)(door.x + dist)] == 'O')
	// 	var->map.map[(int)door.y][(int)(door.x + dist)] = 'D';
	// else if (var->map.map[(int)door.y][(int)(door.x - dist)] == 'O')
	// 	var->map.map[(int)door.y][(int)(door.x - dist)] = 'D';
	// else if (var->map.map[(int)(door.y + dist)][(int)(door.x)] == 'O')
	// 	var->map.map[(int)(door.y + dist)][(int)(door.x)] = 'D';
	// else if (var->map.map[(int)(door.y - dist)][(int)(door.x)] == 'O')
	// 	var->map.map[(int)(door.y - dist)][(int)(door.x)] = 'D';
}

int	handle_keyrelease(int keycode, t_var *var)
{
	if (keycode == 53)
		exit(0);
	if (keycode == LINUX_X)
		open_door(var);
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