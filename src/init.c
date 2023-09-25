/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:53:57 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/25 18:54:39 by nwai-kea         ###   ########.fr       */
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

void	rotate(t_rc *rc, char dir)
{
	if (dir == 'N')
		rotate_north(rc);
	else if (dir == 'S')
		rotate_south(rc);
	else if (dir == 'E')
		rotate_east(rc);
	else if (dir == 'W')
		rotate_west(rc);
}

int	init_var(t_var *var)
{
	var->max_h = 1920;
	var->max_w = 1080;
	var->h = 300;
	var->w = 300;
	ft_bzero(&var->map, sizeof(t_map));
	ft_bzero(&var->tex, sizeof(t_tex));
	ft_bzero(&var->rc, sizeof(t_rc));
	ft_bzero(&var->screen, sizeof(t_img));
	if (!init_mlx(&var->screen, var->max_h, var->max_w))
		error_mes("Mlx parsing error!");
	rotate(&var->rc, &var->map.dir);
	var->rc.mapX = (int)var->map.loc_x;
	var->rc.mapY = (int)var->map.loc_y;
	return (0);
}
