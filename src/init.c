/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:53:57 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/18 16:47:19 by nwai-kea         ###   ########.fr       */
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

void	rotate(t_var *var, char dir)
{
	if (dir == 'N')
		var->map.angle = 0;
	else if (dir == 'S')
		var->map.angle = 180;
	else if (dir == 'E')
		var->map.angle = 90;
	else if (dir == 'W')
		var->map.angle = 270;
}

int	init_minimap(t_img *minimap, void *mlx, int w, int h)
{
	minimap->img = mlx_new_image(mlx, w, h);
	minimap->addr = mlx_get_data_addr(minimap->img, &minimap->bits_per_pixel,
			&minimap->line_length, &minimap->endian);
	return (0);
}

int	init_var(t_var *var)
{
	int	sec;

	var->max_h = S_HEIGHT;
	var->max_w = S_WIDTH;
	var->h = TEX_HEIGHT;
	var->w = TEX_WIDTH;
	sec = 0;
	var->sec = &sec;
	ft_bzero(&var->map, sizeof(t_map));
	ft_bzero(&var->tex, sizeof(t_tex));
	ft_bzero(&var->rc, sizeof(t_rc));
	ft_bzero(&var->screen, sizeof(t_img));
	if (!init_mlx(&var->screen, var->max_h - 1, var->max_w - 1))
		error_mes("Mlx parsing error!", var);
	return (0);
}
