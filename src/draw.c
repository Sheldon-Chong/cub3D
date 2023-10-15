/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:47:09 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/16 00:27:20 by nwai-kea         ###   ########.fr       */
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

// void	dda(t_rc *rc, t_map *map)
// {
// 	rc->hit = 0;
// 	while (rc->hit == 0)
// 	{
// 		if (rc->side_x < rc->side_y)
// 		{
// 			rc->side_x += rc->delta_x;
// 			rc->map_x += rc->step_x;
// 			rc->side = 0;
// 		}
// 		else
// 		{
// 			rc->side_y += rc->delta_y;
// 			rc->map_y += rc->step_y;
// 			rc->side = 1;
// 		}
// 		if (map->map[rc->map_x][rc->map_y] == 1)
// 			rc->hit = 1;
// 	}
// }

// void	ray_distance(t_rc *rc, t_var *var)
// {
// 	if (rc->side == 0)
// 		rc->perp_dist = rc->side_x - rc->delta_x;
// 	else
// 		rc->perp_dist = rc->side_y - rc->delta_y;
// 	rc->line_height = (int)(var->max_h / rc->perp_dist);
// 	rc->start = (-1 * rc->line_height) / 2 + (var->max_h / 2);
// 	if (rc->start < 0)
// 		rc->start = 0;
// 	rc->end = (rc->line_height / 2) + (var->max_h / 2);
// 	if (rc->end >= var->max_h)
// 		rc->end = var->max_h - 1;
// }

// void	draw_bg(t_var *var)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < var->max_h / 2)
// 	{
// 		j = -1;
// 		while (++j < var->max_w)
// 		{
// 			put_pixel(&var->screen, j, i, rgb(var->tex.c[0], var->tex.c[1],
// 						var->tex.c[2]));
// 		}
// 		i++;
// 	}
// 	while (i < var->max_h)
// 	{
// 		j = -1;
// 		while (++j < var->max_w)
// 		{
// 			put_pixel(&var->screen, j, i, rgb(var->tex.f[0], var->tex.f[1],
// 						var->tex.f[2]));
// 		}
// 		i++;
// 	}
// }

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

void	cast_ray(t_var *var, t_xy start, double dir, t_rc *rays)
{
	int		corner;
	t_rc	*rc;
	t_xy	end_pos;

	dir = deg2rad(dir);
	rc = rc_init(start, dir);
	decide_direction(rc);
	while (rc->length < 10)
	{
		corner = ray_goto_next_cell(rc);
		if (rc->current_cell.x > 0 && rc->current_cell.y > 0
			&& rc->current_cell.x < 30 && rc->current_cell.y < 30)
		{
			if (var->map.map[(int)rc->current_cell.y][(int)rc->current_cell.x] == '1')
			{
				end_pos = (t_xy){rc->start.x + rc->length * cos(dir),
									rc->start.y + rc->length * sin(dir)};
				if (rc->xy == 0)
					set_ray_textures("SN"[(rc->dir.y) > 0], rc, end_pos, var);
				if (rc->xy == 1)
					set_ray_textures("WE"[(rc->dir.y) > 0], rc, end_pos, var);
				break ;
			}
			else if (corner == 1
					&& var->map.map[(int)rc->current_cell.y][(int)rc->current_cell.x] == '1')
				break ;
		}
	}
	if (rc->length > 10)
		rc->length = 10;
	else if (rc->length == 10)
		rc->length = 0;
	rays[0] = *rc;
}

int	get_color(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0)
		return (0); // Return a default color when out of bounds
	src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

int	render_3d_view(t_var *var, t_rc *rays, int ray_count)
{
	int		i;
	float	fov;
	float	proj_dist;
	int		color;
	float	ray_dir;
	float	ray_pos;
	short	curr_col;
	short	next_col;
	float	next_ray;
	int		j;
	t_img	tex;
	float	shape_height;
	t_xy	start;

	fov = 66.5;
	proj_dist = 0.5f * CELL_SIZE / tan(deg2rad(0.5f * 58.75f));
	draw_rect(&var->screen, (t_xy){0, 0}, (t_xy){SCREEN_WIDTH, SCREEN_HEIGHT
			/ 2}, rgb(var->tex.c[0], var->tex.c[1], var->tex.c[2]));
	draw_rect(&var->screen, (t_xy){0, SCREEN_HEIGHT / 2}, (t_xy){SCREEN_WIDTH,
			SCREEN_HEIGHT / 2 - 1}, rgb(var->tex.f[0], var->tex.f[1],
				var->tex.f[2]));
	i = -1;
	while (++i < ray_count)
	{
		ray_dir = fov * (floor(0.5f * SCREEN_WIDTH) - i) / (SCREEN_WIDTH - 1);
		ray_pos = 0.5f * tan(deg2rad(ray_dir)) / tan(deg2rad(0.5f * fov));
		curr_col = round(SCREEN_WIDTH * (0.5f - ray_pos));
		next_col = SCREEN_WIDTH;
		if (i < SCREEN_WIDTH - 1)
		{
			next_ray = fov * (floor(0.5f * SCREEN_WIDTH) - 1 - i)
				/ (SCREEN_WIDTH - 1);
			ray_pos = 0.5f * tan(deg2rad(next_ray)) / tan(deg2rad(0.5f * fov));
			next_col = round(SCREEN_WIDTH * (0.5f - ray_pos));
		}
		if (rays[i].length > 0)
		{
			j = -1;
			tex = *(rays[i].texture);
			while (++j < var->h)
			{
				shape_height = round(SCREEN_HEIGHT * proj_dist
						/ ((rays[i].length * 40) * cos(deg2rad(ray_dir))));
				start = (t_xy){curr_col, ((SCREEN_HEIGHT - shape_height)) / 2
					+ (shape_height * ((double)j / var->h))};
				if (rays[i].texture)
					color = get_color(tex.img, var->w - rays[i].texture_column
							- 1, j);
				if (start.x < SCREEN_WIDTH && start.x > 0)
					draw_rect(var->screen.img, start, (t_xy){next_col
							- curr_col, (shape_height * (1 / (double)var->h))},
							color);
			}
		}
	}
	return (1);
}

int	draw_img(void *params)
{
	t_var	*var;
	t_rc	*rays;
	int		ray_count;
	int		i;

	var = (t_var *)params;
	ray_count = SCREEN_WIDTH;
	(*(var->sec))++;
	if (*(var->sec) > 300)
	{
		rays = malloc(sizeof(t_rc) * (ray_count + 1));
		i = -1;
		while (++i < ray_count)
			cast_ray(var, (t_xy){var->map.loc_x, var->map.loc_y}, var->map.angle
					+ (float)(i - (ray_count * 0.5)) / 10, rays + i);
		render_3d_view(var, rays, ray_count);
		free(rays);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
				var->screen.img, 0, 0);
		*(var->sec) = 0;
	}
	return (1);
	// x = 0;
	// draw_bg(var);
	// mlx_put_image_to_window(var->screen.mlx, var->screen.win,
	// var->screen.img,
	// 		0, 0);
	// while (x < var->max_w)
	// {
	// 	var->rc.cam = 2 * x / (double)var->max_w - 1;
	// 	var->rc.ray_x = var->rc.dir_x + var->rc.plane_x * var->rc.cam;
	// 	var->rc.ray_y = var->rc.dir_y + var->rc.plane_y * var->rc.cam;
	// 	var->rc.delta_x = fabs(1 / var->rc.dir_x);
	// 	var->rc.delta_y = fabs(1 / var->rc.dir_y);
	// 	cal_steps(var);
	// 	dda(&var->rc, &var->map);
	// 	ray_distance(&var->rc, var);
	// 	draw_tex(&var, x);
	// 	x++;
	// }
}
