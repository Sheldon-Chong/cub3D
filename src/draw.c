/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:47:09 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/30 13:34:06 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	decide_direction(t_rc *rc)
{
	if (rc->dir.x < 0)
	{
		rc->cell_step.x = -1;
		rc->distance.x = (rc->start.x / CELL_SIZE - rc->current_cell.x)
			* rc->unit_length.x;
	}
	else
	{
		rc->cell_step.x = 1;
		rc->distance.x = ((1 + rc->current_cell.x) - rc->start.x / CELL_SIZE)
			* rc->unit_length.x;
	}
	if (rc->dir.y < 0)
	{
		rc->cell_step.y = -1;
		rc->distance.y = (rc->start.y / CELL_SIZE - rc->current_cell.y)
			* rc->unit_length.y;
	}
	else
	{
		rc->cell_step.y = 1;
		rc->distance.y = ((1 + rc->current_cell.y) - rc->start.y / CELL_SIZE)
			* rc->unit_length.y;
	}
}

int	ray_goto_next_cell(t_rc *rc)
{
	int	coll;

	coll = 0;
	if (rc->distance.x < rc->distance.y)
	{
		rc->length = rc->distance.x;
		rc->distance.x += rc->unit_length.x;
		rc->current_cell.x += rc->cell_step.x;
		rc->xy = 1;
	}
	else if (rc->distance.x > rc->distance.y)
	{
		rc->length = rc->distance.y;
		rc->distance.y += rc->unit_length.y;
		rc->current_cell.y += rc->cell_step.y;
		rc->xy = 0;
	}
	else
	{
		coll = 1;
		rc->length = rc->distance.x;
		rc->distance.x += rc->unit_length.x;
		rc->distance.y += rc->unit_length.y;
		rc->current_cell.x += rc->cell_step.x;
		rc->current_cell.y += rc->cell_step.y;
	}
	return (coll);
}

t_xy	cell(t_xy pos)
{
	return ((t_xy){pos.x * CELL_SIZE, pos.y * CELL_SIZE});
}

void	draw_rectquare(void *mlx, void *mlx_win, t_xy start, t_xy wh, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < wh.y)
	{
		x = -1;
		while (++x < wh.x)
			mlx_pixel_put(mlx, mlx_win, x + start.x, y + start.y, color);
	}
}

void	draw_grid(void *mlx, void *win, t_xy cell_wh, t_xy gap_wh, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cell_wh.y)
	{
		x = -1;
		while (++x < cell_wh.x)
		{
			draw_rectquare(mlx, win, (t_xy){x * gap_wh.x, y * gap_wh.y},
					(t_xy){2, 2}, COLOR_RED);
			if (map[y][x] == '1')
				draw_rectquare(mlx, win, (t_xy){x * CELL_SIZE, y * CELL_SIZE},
						(t_xy){CELL_SIZE, CELL_SIZE}, COLOR_RED);
		}
	}
}

t_xy	draw_line_dir(t_img *img, t_xy start, double direction,
	double distance, int color)
{
	double	step = 0.1;
	double	t = 0;

	while (t <= distance)
	{
		put_pixel(img, start.x + t * cos(direction), start.y + t * sin(direction), color);
		t += step;
	}
	return ((t_xy){start.x + distance * cos(direction), start.y + distance
		* sin(direction)});
}

void	set_ray_textures(char c, t_rc *rc, t_xy end_pos, t_var *var)
{
	double	dif;

	dif = 0;
	if (c == 'N')
	{
		dif = end_pos.x - rc->current_cell.x;
		rc->texture = var->tex.n;
	}
	else if (c == 'S')
	{
		dif = end_pos.x - rc->current_cell.x;
		rc->texture = var->tex.s;
	}
	else if (c == 'E')
	{
		dif = end_pos.y - rc->current_cell.y;
		rc->texture = var->tex.e;
	}
	else if (c == 'W')
	{
		dif = end_pos.y - rc->current_cell.y;
		rc->texture = var->tex.w;
	}
	rc->texture_column = (int)(dif * var->w);
}

int	view_depth(int w, int h)
{
	if (w >= h)
		return (w);
	else
		return (h);
}

t_rc	*rc_init(t_xy start, double direction)
{
	t_rc	*rc;

	rc = malloc(sizeof(t_rc));
	rc->dir = (t_xy){cos(direction), sin(direction)};
	rc->angle = direction;
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
	decide_direction(rc);
	return (rc);
}

double	cast_ray(t_var *var, t_xy start, double dir, t_rc *rays)
{
	t_rc	*rc;
	t_xy	end_pos;
	int		l;

	dir = deg2rad(dir);
	rc = rc_init(start, dir);
	
	while (rc->length < 100)
	{
		ray_goto_next_cell(rc);
		if (var->map.map[(int)rc->current_cell.y][(int)rc->current_cell.x] == '1')
		{
			end_pos = draw_line_dir(&var->minimap,
					(t_xy){start.x, start.y}, dir, rc->length, COLOR_CYAN);
			draw_line_dir(&var->minimap,
				(t_xy){start.x * MMAP_SIZE, start.y * MMAP_SIZE},
				dir, rc->length * MMAP_SIZE, rgb(200, 200, 200));
			if (rc->xy == 0)
				set_ray_textures("SN"[(rc->dir.y) > 0], rc, end_pos, var);
			if (rc->xy == 1)
				set_ray_textures("WE"[(rc->dir.x) > 0], rc, end_pos, var);
			break ;
		}
	}
	rc->length *= cos(deg2rad((double)var->map.angle) - (rc->angle));
	rays[0] = *rc;
	return (rc->length);
}

int	get_color(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0)
		return (0);
	src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

void	render_3d_view(t_var *var, t_rc *rays, int ray_count)
{
	int		x;
	int		y;
	float	shape_height;
	t_xy	shape_start;

	draw_rect(&var->screen, (t_xy){0, 0}, (t_xy){SCREEN_WIDTH, SCREEN_HEIGHT
		/ 2}, var->tex.ceiling);
	draw_rect(&var->screen, (t_xy){0, SCREEN_HEIGHT / 2}, (t_xy){SCREEN_WIDTH,
		SCREEN_HEIGHT / 2 - 1}, var->tex.floor);
	x = -1;
	while (++x < ray_count)
	{
		shape_height = (SCREEN_HEIGHT / ((rays[x].length)));
		y = -1;
		while (++y < var->h)
		{
			shape_start = (t_xy){x, ((SCREEN_HEIGHT - shape_height)) / 2
				+ (shape_height * ((double)y / var->h))};
			if (shape_start.x < SCREEN_WIDTH && shape_start.x > 0)
				draw_rect(&var->screen, (t_xy){shape_start.x, shape_start.y},
					(t_xy){1, (shape_height * (1 / (double)var->h))},
					get_color(rays[x].texture,
						var->w - rays[x].texture_column - 1, y));
			if (shape_start.y > SCREEN_HEIGHT
				|| shape_start.x > SCREEN_WIDTH)
				break ;
		}
	}
}

void draw_minimap(t_var *var)
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
			if (var->map.map[(int)pos.y][(int)pos.x] == '1')
				draw_rect(&var->minimap, (t_xy){pos.x * MMAP_SIZE, pos.y
					* MMAP_SIZE}, (t_xy){MMAP_SIZE, MMAP_SIZE}, rgb(0, 0, 0));
	}
	draw_rect(&var->minimap, (t_xy){var->map.loc_x * MMAP_SIZE,
		var->map.loc_y * MMAP_SIZE}, (t_xy){5, 5}, COLOR_BLACK);
	draw_line_dir(&var->minimap, (t_xy){var->map.loc_x * MMAP_SIZE,
		var->map.loc_y * MMAP_SIZE},
		deg2rad(var->map.angle), MMAP_SIZE, COLOR_CYAN);
}

void draw_ui(t_var *var)
{
	draw_rect(&var->ui, (t_xy){60, 250}, (t_xy){450, 30}, COLOR_BLACK);
	draw_rect(&var->ui, (t_xy){60, 250}, (t_xy){450*(7.0/10.0), 30}, COLOR_RED);
	mlx_put_image_to_window(var->screen.mlx, var->screen.win, var->player_pov.img, 
		SCREEN_WIDTH - var->player_pov.width, SCREEN_HEIGHT - var->player_pov.height);
	return ;
}

t_rc	*cast_rays(t_var *var, int ray_count)
{
	t_rc	*rays;
	int		i;
	
	i = -1;
	rays = malloc(sizeof(t_rc) * (ray_count + 1));
	while (++i < ray_count)
	{
		cast_ray(var, (t_xy){var->map.loc_x, var->map.loc_y},var->map.angle
				+ (float)(i - (ray_count * 0.5)) / 20, rays + i);
		if(i < ray_count && rays[i].length < 0.2)
		{
			if(i + 1 < ray_count)
				rays[i + 1] = rays[i];
			if(i + 2 < ray_count)
				rays[i + 2] = rays[i];
			i += 2;
		}
	}
	return(rays);
}

int	draw_img(void *params)
{
	t_var		*var;
	t_rc		*screen;
	int			ray_count;
	double		i;

	var = (t_var *)params;
	ray_count = SCREEN_WIDTH;
	(*(var->sec))++;
	if (*(var->sec) > 100)
	{
		draw_minimap(var);
		screen = cast_rays(var, SCREEN_WIDTH);
		render_3d_view(var, screen, ray_count);
		free(screen);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
				var->screen.img, 0, 0);
		draw_ui(var);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
				var->ui.img, 0, 0);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
				var->heart.img, 20, 235);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
			var->minimap.img, 20, 20);
		*(var->sec) = 0;
	}
	return (1);
}
