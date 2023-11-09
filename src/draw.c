/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:47:09 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/10 00:04:57 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d_view(t_var *var, t_rc *rays, int ray_count)
{
	int		x;
	int		y;
	float	shape_height;
	t_xy	shape_start;

	x = -1;
	while (++x < ray_count)
	{
		shape_height = (SCREEN_HEIGHT / ((rays[x].length)));
		y = -1;
		if(rays[x].c != 'd')
		{
			while (++y < var->h)
			{
				shape_start = (t_xy){x, ((SCREEN_HEIGHT - shape_height)) / 2
					+ (shape_height * ((double)y / var->h))};
				draw_rect(&var->screen, (t_xy){shape_start.x, shape_start.y},
					(t_xy){1, (shape_height * (1 / (double)var->h))},
					get_color(rays[x].texture,
						var->w - rays[x].texture_column - 1, y));
				if (shape_start.y > SCREEN_HEIGHT || shape_start.x > SCREEN_WIDTH)
					break ;
			}
		}
		else
		{
			shape_start = (t_xy){x, ((SCREEN_HEIGHT - shape_height)) / 2
				+ (shape_height * ((double)y / var->h))};
			draw_rect(&var->screen, (t_xy){shape_start.x, shape_start.y},
				(t_xy){1, shape_height}, rgb(100,100,100));
			if (shape_start.y > SCREEN_HEIGHT || shape_start.x > SCREEN_WIDTH)
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
		draw_rect(&var->minimap, (t_xy){pos.x * MMAP_SIZE, 0},
			(t_xy){1, var->map.height * MMAP_SIZE}, COLOR_WHITE);
	while (++pos.y < var->map.height)
		draw_rect(&var->minimap, (t_xy){0, pos.y * MMAP_SIZE},
			(t_xy){var->map.width * MMAP_SIZE, 1}, COLOR_WHITE);
	pos = (t_xy){-1, -1};
	while (++pos.y < var->map.height)
	{
		pos.x = -1;
		while (++pos.x < var->map.width)
		{
			if (var->map.map[(int)pos.y][(int)pos.x] == '1')
				draw_rect(&var->minimap, (t_xy){pos.x * MMAP_SIZE, pos.y
					* MMAP_SIZE}, (t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(0, 0, 0));
			if (var->map.map[(int)pos.y][(int)pos.x] == 'D')
				draw_rect(&var->minimap, (t_xy){pos.x * MMAP_SIZE, pos.y
					* MMAP_SIZE}, (t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(255, 255, 30));
			if (var->map.map[(int)pos.y][(int)pos.x] == 'd')
				draw_rect(&var->minimap, (t_xy){pos.x * MMAP_SIZE, pos.y
					* MMAP_SIZE}, (t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(0, 255, 0));
		}
	}
	draw_rect(&var->minimap, (t_xy){var->map.pos.x * MMAP_SIZE,
		var->map.pos.y * MMAP_SIZE}, (t_xy){5, 5}, COLOR_BLACK);
	draw_line_dir(&var->minimap, (t_xy){var->map.pos.x * MMAP_SIZE,
		var->map.pos.y * MMAP_SIZE},
		deg2rad(var->map.angle), MMAP_SIZE, COLOR_CYAN);
}

void	draw_ui(t_var *var)
{
	mlx_put_image_to_window(var->screen.mlx,
		var->screen.win, var->frames[var->frame_num]->img,
		SCREEN_WIDTH - var->player_pov->width + 1100,
		SCREEN_HEIGHT - var->player_pov->height + 200);
	mlx_put_image_to_window(var->screen.mlx, var->screen.win,
		var->minimap.img, 20, 20);
	return ;
}

int	draw_img(void *params)
{
	t_var		*var;
	t_rc		*screen;
	int			i;

	i = -1;
	var = (t_var *)params;
	if ((*(var->sec))++ > 100)
	{
		if(var->fire)
			var->frame_num++;
		if (var->frame_num > 6)
		{
			var->frame_num = 0;
			var->fire = 0;
		}
		draw_rect(&var->screen, (t_xy){0, 0}, (t_xy){SCREEN_WIDTH, SCREEN_HEIGHT
			/ 2}, var->tex.ceiling);
		draw_rect(&var->screen, (t_xy){0, SCREEN_HEIGHT / 2},
			(t_xy){SCREEN_WIDTH, SCREEN_HEIGHT / 2 - 1}, var->tex.floor);
		draw_minimap(var);
		screen = cast_rays(var, SCREEN_WIDTH);
		render_3d_view(var, screen, SCREEN_WIDTH);
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
