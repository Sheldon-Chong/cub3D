/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:47:09 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/25 15:02:20 by shechong         ###   ########.fr       */
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

void	cast_ray(t_var *var, t_xy start, double dir, t_rc *rays)
{
	int		corner;
	t_rc	*rc;
	t_xy	end_pos;
	int		l;

	dir = deg2rad(dir);
	
	rc = rc_init(start, dir);
	// printf("%f | %f\n", (*rc).angle, rays->angle);
	rays->angle = dir;
	decide_direction(rc);
	l = view_depth(var->map.width, var->map.height);
	while (rc->length < l)
	{
		corner = ray_goto_next_cell(rc);
		if (var->map.map[(int)rc->current_cell.y][(int)rc->current_cell.x] == '1')
		{
			end_pos = draw_line_dir(&var->minimap,
					(t_xy){start.x, start.y}, dir, rc->length, COLOR_CYAN);
			draw_line_dir(&var->minimap,(t_xy){start.x * MINIMAP_SCALE, start.y * MINIMAP_SCALE}, dir, rc->length * MINIMAP_SCALE, rgb(200,200,200));
			if (rc->xy == 0)
				set_ray_textures("SN"[(rc->dir.y) > 0], rc, end_pos, var);
			if (rc->xy == 1)
				set_ray_textures("WE"[(rc->dir.x) > 0], rc, end_pos, var);
			break ;
		}
		else if (corner == 1
				&& var->map.map[(int)rc->current_cell.y][(int)rc->current_cell.x] == '1')
			break ;
	}
	if (rc->length == l)
		rc->length = 0;
	rays[0] = *rc;
	
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
	int		i;
	int		j;
	float	proj_dist;
	float	shape_height;
	t_xy	start;

	draw_rect(&var->screen, (t_xy){0, 0}, (t_xy){SCREEN_WIDTH, SCREEN_HEIGHT
			/ 2}, rgb(var->tex.c[0], var->tex.c[1], var->tex.c[2]));
	draw_rect(&var->screen, (t_xy){0, SCREEN_HEIGHT / 2}, (t_xy){SCREEN_WIDTH,
			SCREEN_HEIGHT / 2 - 1}, rgb(var->tex.f[0], var->tex.f[1], var->tex.f[2]));
	proj_dist = 0.5f * CELL_SIZE / tan(deg2rad(0.5f * 58.75f));
	i = -1;
	while (++i < ray_count)
	{
		if (rays[i].length > 0)
		{
			j = -1;
			while (++j < var->h)
			{
				shape_height = round(SCREEN_HEIGHT * proj_dist / ((rays[i].length) * 20));
				start = (t_xy){i, ((SCREEN_HEIGHT - shape_height)) / 2 + (shape_height * ((double)j / var->h))};
				if (start.x < SCREEN_WIDTH && start.x > 0)
					draw_rect(&var->screen, start, (t_xy){1, (shape_height * (1 / (double)var->h))},
						get_color(rays[i].texture, var->w - rays[i].texture_column - 1, j));
			}
		}
	}
}

void draw_minimap(t_var *var)
{
	t_xy pos; 
	
	draw_rect(&var->minimap, (t_xy){0,0}, (t_xy){var->map.width * MINIMAP_SCALE,var->map.height * MINIMAP_SCALE}, rgb(200,100,100));

	pos = (t_xy){-1,-1};
	while(++pos.x < var->map.width)
		draw_rect(&var->minimap, (t_xy){pos.x * MINIMAP_SCALE,0}, (t_xy){1,var->map.height * MINIMAP_SCALE}, rgb(255,255,255));
	while(++pos.y < var->map.height)
		draw_rect(&var->minimap, (t_xy){0,pos.y * MINIMAP_SCALE}, (t_xy){var->map.width * MINIMAP_SCALE,1}, rgb(255,255,255));
	pos = (t_xy){-1,-1};
	while(++pos.y < var->map.height)
	{
		pos.x = - 1;
		while(++pos.x < var->map.width)
			if(var->map.map[(int)pos.y][(int)pos.x] == '1')
				draw_rect(&var->minimap, (t_xy){pos.x * MINIMAP_SCALE,pos.y * MINIMAP_SCALE}, (t_xy){MINIMAP_SCALE,MINIMAP_SCALE}, rgb(0,0,0));
	}
	draw_rect(&var->minimap, (t_xy){var->map.loc_x * MINIMAP_SCALE,var->map.loc_y * MINIMAP_SCALE}, (t_xy){5,5}, rgb(0,0,0));
	draw_line_dir(&var->minimap, (t_xy){var->map.loc_x*MINIMAP_SCALE,var->map.loc_y*MINIMAP_SCALE}, deg2rad(var->map.angle), MINIMAP_SCALE, COLOR_CYAN);
	
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
		draw_minimap(var);

		rays = malloc(sizeof(t_rc) * (ray_count + 1));
		i = -1;
		while (++i < ray_count)
			cast_ray(var, (t_xy){var->map.loc_x, var->map.loc_y}, var->map.angle
					+ (float)(i - (ray_count * 0.5)) / 33, rays + i);		
		render_3d_view(var, rays, ray_count);
		free(rays);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
				var->screen.img, 0, 0);
		mlx_put_image_to_window(var->screen.mlx, var->screen.win,
			var->minimap.img, 20, 20);
		*(var->sec) = 0;
	}
	return (1);
}
