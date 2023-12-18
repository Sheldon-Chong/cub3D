/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:44:40 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/18 19:39:25 by nwai-kea         ###   ########.fr       */
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
	else if (frame->map.map[(int)new_pos.y][(int)(new_pos.x + dist)] == 'D'
			|| frame->map.map[(int)new_pos.y][(int)(new_pos.x - dist)] == 'D'
			|| frame->map.map[(int)(new_pos.y + dist)][(int)(new_pos.x)] == 'D'
			|| frame->map.map[(int)(new_pos.y - dist)][(int)(new_pos.x)] == 'D')
		return ;
	if (frame->map.map[(int)new_pos.y][(int)new_pos.x] != '1'
		|| frame->map.map[(int)new_pos.y][(int)new_pos.x] != 'D')
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
	if (keycode == 124)
		var->map.angle += 5;
	if (keycode == 123)
		var->map.angle -= 5;
	return (0);
}

int	mouse_move(int x, int y, t_var *var)
{
	mlx_mouse_hide();
	mlx_mouse_move(var->screen.win, S_WIDTH / 2, S_HEIGHT / 2);
	var->map.angle -= ((S_WIDTH / 2 - x) * 0.08);
	y++;
	return (0);
}

int	shoot(int keycode, int x, int y, t_var *var)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		var->fire = 1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 2)
		error_mes_argc("Error: Invalid Number of Arguments.\n");
	if (init_var(&var) || parse_file(argv[1], &var)
		|| init_minimap(&var.minimap, var.screen.mlx, var.map.width * MMAP_SIZE,
			var.map.height * MMAP_SIZE))
		error_mes("Error: Parsing error", &var);
	rotate(&var, var.map.dir);
	var.map.angle -= 90;
	insert_frames(&var);
	mlx_hook(var.screen.win, 2, 1L << 0, handle_keypress, &var);
	mlx_hook(var.screen.win, 6, 0, mouse_move, &var);
	mlx_hook(var.screen.win, 3, 0, handle_keyrelease, &var);
	mlx_hook(var.screen.win, 17, 1L << 17, exit_program, &var);
	mlx_mouse_hook(var.screen.win, shoot, &var);
	mlx_loop_hook(var.screen.mlx, draw_img, &var);
	mlx_loop(var.screen.mlx);
}
