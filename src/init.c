/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:53:57 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/19 00:24:11 by nwai-kea         ###   ########.fr       */
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

int	init_var(t_var *var)
{
	// t_map	map;
	var->max_h = 1920;
	var->max_w = 1080;
	if (!init_mlx(&var->screen, var->max_h, var->max_w))
		error_mes("Mlx parsing error!");
	return (0);
	// init_map(var->map);
}
