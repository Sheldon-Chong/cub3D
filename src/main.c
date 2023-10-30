/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:44:40 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/30 14:34:22 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_var *frame, t_xy dir_vec)
{
	t_xy	new_pos;
	double	dist;

	dist = 0.05;
	new_pos = op((t_xy){frame->map.pos.x, frame->map.pos.y}, dir_vec, '+');
	if (frame->map.map[(int)new_pos.y][(int)(new_pos.x + dist)] == '1'
	|| frame->map.map[(int)new_pos.y][(int)(new_pos.x - dist)] == '1'
	|| frame->map.map[(int)(new_pos.y + dist)][(int)(new_pos.x)] == '1'
	|| frame->map.map[(int)(new_pos.y - dist)][(int)(new_pos.x)] == '1')
		return ;
	if (frame->map.map[(int)new_pos.y][(int)new_pos.x] != '1')
	{
		frame->map.pos.x = new_pos.x;
		frame->map.pos.y = new_pos.y;
	}
}

int	handle_keypress(int keycode, t_var *var)
{
	double	amount;

	amount = 0.1;
	if (keycode == LINUX_W)
		move_player(var, op(angle_to_vector(deg2rad(var->map.angle)),
				(t_xy){amount, amount}, '*'));
	if (keycode == LINUX_A)
		move_player(var, op(angle_to_vector(deg2rad(var->map.angle - 90)),
				(t_xy){amount, amount}, '*'));
	if (keycode == LINUX_S)
		move_player(var, op(angle_to_vector(deg2rad(var->map.angle + 180)),
				(t_xy){amount, amount}, '*'));
	if (keycode == LINUX_D)
		move_player(var, op(angle_to_vector(deg2rad(var->map.angle + 90)),
				(t_xy){amount, amount}, '*'));
	if (keycode == LINUX_E)
		var->map.angle += 5;
	if (keycode == LINUX_Q)
		var->map.angle -= 5;
	if (keycode == 53)
		exit(0);
	return (0);
}

int	mouse_move(int x, int y, t_var *var)
{
	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
	{
		var->mouse_x = x;
		var->mouse_y = y;
		return (0);
	}
	if (x < var->mouse_x)
		var->map.angle -= 5;
	else if (x > var->mouse_x)
		var->map.angle += 5;
	var->mouse_x = x;
	var->mouse_y = y;
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		sec;

	if (argc != 2)
		error_mes("Invalid Number of Arguments.\n");
	if (init_var(&var) || parse_file(argv[1], &var)
		|| init_minimap(&var.minimap, var.screen.mlx, var.map.width
			* MMAP_SIZE, var.map.height * MMAP_SIZE)
		|| init_ui(&var.ui, var.screen.mlx))
		return (1);
	rotate(&var, var.map.dir);
	var.map.pos.y += 0.2;
	var.player_pov.img = mlx_xpm_file_to_image(var.screen.mlx,
			"gun.xpm", &var.player_pov.width, &var.player_pov.height);
	var.heart.img = mlx_xpm_file_to_image(var.screen.mlx,
			"cross.xpm", &var.heart.width, &var.heart.height);
	mlx_hook(var.screen.win, 2, 1L << 0, handle_keypress, &var);
	mlx_hook(var.screen.win, 6, 0, mouse_move, &var);
	mlx_loop_hook(var.screen.mlx, draw_img, &var);
	mlx_loop(var.screen.mlx);
	return (0);
}
