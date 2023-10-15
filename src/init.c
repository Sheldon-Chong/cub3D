/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:53:57 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/16 00:41:15 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_img *screen, int h, int w)
{
	screen->mlx = mlx_init();
	if (!screen->mlx)
		return (0);
	screen->win = mlx_new_window(screen->mlx, w, h, "cub3d");
	screen->img = mlx_new_image(screen->mlx, w, h);
	screen->addr = mlx_get_data_addr(screen->img, &screen->bits_per_pixel,
			&screen->line_length, &screen->endian);
	return (1);
}

// void	rotate(t_rc *rc, char dir)
// {
// 	if (dir == 'N')
// 		rotate_north(rc);
// 	else if (dir == 'S')
// 		rotate_south(rc);
// 	else if (dir == 'E')
// 		rotate_east(rc);
// 	else if (dir == 'W')
// 		rotate_west(rc);
// }

t_rc	*rc_init(t_xy start, double direction)
{
	t_rc	*rc;

	rc = malloc(sizeof(t_rc));
	rc->dir = (t_xy){cos(direction), sin(direction)};
	rc->start = (t_xy){start.x * CELL_SIZE, start.y * CELL_SIZE};
	rc->current_cell = (t_xy){floor(rc->start.x / CELL_SIZE), floor(rc->start.y
			/ CELL_SIZE)};
	rc->cell_step = (t_xy){0, 0};
	rc->unit_length.x = sqrt(1.0 + (rc->dir.y / rc->dir.x) * (rc->dir.y
				/ rc->dir.x));
	rc->unit_length.y = sqrt(1.0 + (rc->dir.x / rc->dir.y) * (rc->dir.x
				/ rc->dir.y));
	rc->distance = (t_xy){0, 0};
	rc->length = 0;
	return (rc);
}

int	init_var(t_var *var)
{
	int	sec;

	var->max_h = SCREEN_HEIGHT;
	var->max_w = SCREEN_WIDTH;
	var->h = TEX_HEIGHT;
	var->w = TEX_WIDTH;
	sec = 0;
	var->sec = &sec;
	ft_bzero(&var->map, sizeof(t_map));
	ft_bzero(&var->tex, sizeof(t_tex));
	ft_bzero(&var->rc, sizeof(t_rc));
	ft_bzero(&var->screen, sizeof(t_img));
	if (!init_mlx(&var->screen, var->max_h - 1, var->max_w - 1))
		error_mes("Mlx parsing error!");
	// rotate(&var->rc, var->map.dir);
	// var->rc.map_x = var->map.loc_x;
	// var->rc.map_y = var->map.loc_y;
	return (0);
}
