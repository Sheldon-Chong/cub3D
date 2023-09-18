/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:45:20 by jakoh             #+#    #+#             */
/*   Updated: 2023/09/18 16:11:32 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture(t_texture *texture)
{
	texture->north = NULL;
	texture->south = NULL;
	texture->east = NULL;
	texture->west = NULL;
	texture->floor = NULL;
	texture->ceiling = NULL;
}

void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->pX = 0;
	map->pY = 0;
	map->map = NULL;
}

int	init_mlx(t_vars *vars)
{
	t_img	mlx;

	ft_bzero(&mlx, sizeof(mlx));
	vars->screen = mlx;
	vars->screen.mlx = mlx_init();
	if (!(vars->screen.mlx))
		return (1);
	vars->screen.win = mlx_new_window(vars->screen.mlx, (int)vars->max_width,
			(int)vars->max_height, "cub3d");
	vars->screen.img = mlx_new_image(vars->screen.mlx, (int)vars->max_width,
			(int)vars->max_height);
	vars->screen.addr = mlx_get_data_addr(vars->screen.img, &vars->screen.bpp,
			&vars->screen.line_length, &vars->screen.endian);
	return (0);
}

void	init_raycast(t_vars *vars)
{
	t_raycast	rc;

	ft_bzero(&rc, sizeof(rc));
	vars->rc = rc;
	vars->rc.pos_x = vars->map.pX + 0.5;
	vars->rc.pos_y = vars->map.pY + 0.5;
	vars->rc.dir_x = -1;
	vars->rc.dir_y = 0;
	vars->rc.plane_x = 0;
	vars->rc.plane_y = 0.66;
	vars->rc.speed = 0.1;
	vars->rc.rot_speed = M_PI / 48;
}

void	init_vars(t_vars *vars)
{
	vars->max_width = 1920;
	vars->max_height = 1080;
	vars->mlx = mlx_init();
	vars->window = mlx_new_window(vars->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	// if (init_mlx(vars) == 1)
	// 	return ;
	init_texture(&vars->texture);
	init_map(&vars->map);
	init_raycast(vars);
}
