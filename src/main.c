/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:44:40 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/20 00:29:29 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_var *frame, t_xy direction_vec)
{
	t_xy	new_pos;

	new_pos = op((t_xy){frame->map.loc_x, frame->map.loc_y}, direction_vec,
			'+');
	if (frame->map.map[(int)new_pos.y][(int)new_pos.x] == '1')
		printf("Wall Collision\n");
	else
	{
		frame->map.loc_x = new_pos.x;
		frame->map.loc_y = new_pos.y;
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
	// if (keycode == 49)
	// 	player->val += 1;
	// if (keycode == 51)
	// 	player->val -= 1;
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

int	init_minimap(t_img *minimap, void *mlx, int w, int h)
{
	minimap->img = mlx_new_image(mlx, w, h);
	minimap->addr = mlx_get_data_addr(minimap->img, &minimap->bits_per_pixel,
			&minimap->line_length, &minimap->endian);
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
			* MINIMAP_SCALE, var.map.height * MINIMAP_SCALE))
		return (1);
	rotate(&var, var.map.dir);
	printf("%d, %d\n", var.map.width, var.map.height);
	mlx_hook(var.screen.win, 2, 1L << 0, handle_keypress, &var);
	mlx_hook(var.screen.win, 6, 0, mouse_move, &var);
	mlx_loop_hook(var.screen.mlx, draw_img, &var);
	mlx_loop(var.screen.mlx);
	return (0);
}
