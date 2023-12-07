/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:47:09 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/07 11:07:57 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d_view(t_var *var, t_rc *rays, int x, int y)
{
	float	height;
	t_xy	start;

	while (++x < S_WIDTH)
	{
		height = (S_HEIGHT / ((rays[x].length)));
		y = -1;
		if (rays[x].c != 'd')
		{
			while (++y < var->h)
			{
				start = get_start(x, height, y, var);
				draw_rect2(var, start, rays[x], y);
				if (start.y > S_HEIGHT || start.x > S_WIDTH)
					break ;
			}
		}
		else
		{
			start = get_start(x, height, y, var);
			draw_rect3(var, height, x, y);
			if (start.y > S_HEIGHT || start.x > S_WIDTH)
				break ;
		}
	}
}

void	draw_minimap(t_var *var)
{
	t_xy	pos;

	draw_rect(&var->minimap, (t_xy){0, 0}, (t_xy){var->map.width * MMAP_SIZE,
		var->map.height * MMAP_SIZE}, rgb(200, 100, 100));
	pos = (t_xy){-1, -1};
	while (++pos.x < var->map.width)
		draw_rect(&var->minimap, (t_xy){pos.x * MMAP_SIZE, 0}, (t_xy){1,
			var->map.height * MMAP_SIZE}, COLOR_WHITE);
	while (++pos.y < var->map.height)
		draw_rect(&var->minimap, (t_xy){0, pos.y * MMAP_SIZE},
			(t_xy){var->map.width * MMAP_SIZE, 1}, COLOR_WHITE);
	pos = (t_xy){-1, -1};
	while (++pos.y < var->map.height)
	{
		pos.x = -1;
		while (++pos.x < var->map.width)
			draw_rectangle(var, pos.x, pos.y);
	}
	draw_rect(&var->minimap, (t_xy){var->map.pos.x * MMAP_SIZE, var->map.pos.y
		* MMAP_SIZE}, (t_xy){5, 5}, COLOR_BLACK);
	draw_line(&var->minimap, (t_xy){var->map.pos.x * MMAP_SIZE, var->map.pos.y
		* MMAP_SIZE}, deg2rad(var->map.angle), MMAP_SIZE);
}

void	draw_ui(t_var *var)
{
	mlx_put_image_to_window(var->screen.mlx,
		var->screen.win,
		var->frames[var->frame_num]->img,
		S_WIDTH - var->player_pov->width + 1100,
		S_HEIGHT - var->player_pov->height + 200);
	mlx_put_image_to_window(var->screen.mlx, var->screen.win, var->minimap.img,
		20, 20);
	return ;
}

int	draw_img(void *params)
{
	t_var	*var;
	t_rc	*screen;

	var = (t_var *)params;
	if ((*(var->sec))++ > 100)
	{
		fire(var);
		draw_rect(&var->screen, (t_xy){0, 0}, (t_xy){S_WIDTH, S_HEIGHT / 2},
			var->tex.ceiling);
		draw_rect(&var->screen, (t_xy){0, S_HEIGHT / 2}, (t_xy){S_WIDTH,
			S_HEIGHT / 2 - 1}, var->tex.floor);
		draw_minimap(var);
		screen = cast_rays(var, S_WIDTH);
		render_3d_view(var, screen, -1, -1);
		free(screen);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
			var->screen.img, 0, 0);
		draw_ui(var);
		*(var->sec) = 0;
	}
	return (1);
}

t_rc	*cast_rays(t_var *var, int ray_count)
{
	t_rc	*rays;
	int		i;

	i = -1;
	rays = malloc(sizeof(t_rc) * (ray_count + 1));
	while (++i < ray_count)
	{
		cast_ray(var, (t_xy){var->map.pos.x, var->map.pos.y}, var->map.angle
			+ (float)(i - (ray_count * 0.5)) / 20, rays + i);
		if (i < ray_count && rays[i].length < 0.2)
		{
			if (i + 1 < ray_count)
				rays[i + 1] = rays[i];
			if (i + 2 < ray_count)
				rays[i + 2] = rays[i];
			i += 2;
		}
	}
	return (rays);
}
