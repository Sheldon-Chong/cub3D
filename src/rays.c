/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:33:24 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/12 00:49:39 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	decide_direction(t_rc *rc)
{
	if (rc->dir.x < 0)
	{
		rc->cell_step.x = -1;
		rc->distance.x = (rc->start.x / CELL_SIZE - rc->curr_cell.x)
			* rc->unit_length.x;
	}
	else
	{
		rc->cell_step.x = 1;
		rc->distance.x = ((1 + rc->curr_cell.x) - rc->start.x / CELL_SIZE)
			* rc->unit_length.x;
	}
	if (rc->dir.y < 0)
	{
		rc->cell_step.y = -1;
		rc->distance.y = (rc->start.y / CELL_SIZE - rc->curr_cell.y)
			* rc->unit_length.y;
	}
	else
	{
		rc->cell_step.y = 1;
		rc->distance.y = ((1 + rc->curr_cell.y) - rc->start.y / CELL_SIZE)
			* rc->unit_length.y;
	}
}

int	ray_goto_next_cell(t_rc *rc)
{
	if (rc->distance.x < rc->distance.y)
	{
		rc->length = rc->distance.x;
		rc->distance.x += rc->unit_length.x;
		rc->curr_cell.x += rc->cell_step.x;
		rc->xy = 1;
	}
	else if (rc->distance.x > rc->distance.y)
	{
		rc->length = rc->distance.y;
		rc->distance.y += rc->unit_length.y;
		rc->curr_cell.y += rc->cell_step.y;
		rc->xy = 0;
	}
	else
	{
		rc->length = rc->distance.x;
		rc->distance.x += rc->unit_length.x;
		rc->distance.y += rc->unit_length.y;
		rc->curr_cell.x += rc->cell_step.x;
		rc->curr_cell.y += rc->cell_step.y;
	}
	return (1);
}

void	set_ray_textures(char c, t_rc *rc, t_xy end_pos, t_var *var)
{
	double	dif;

	dif = 0;
	if (c == 'N')
	{
		dif = end_pos.x - rc->curr_cell.x;
		rc->texture = var->tex.n;
	}
	else if (c == 'S')
	{
		dif = end_pos.x - rc->curr_cell.x;
		rc->texture = var->tex.s;
	}
	else if (c == 'E')
	{
		dif = end_pos.y - rc->curr_cell.y;
		rc->texture = var->tex.e;
	}
	else if (c == 'W')
	{
		dif = end_pos.y - rc->curr_cell.y;
		rc->texture = var->tex.w;
	}
	rc->texture_column = (int)(dif * var->w);
}

t_rc	*rc_init(t_xy start, double direction)
{
	t_rc	*rc;

	rc = malloc(sizeof(t_rc));
	rc->dir = (t_xy){cos(direction), sin(direction)};
	rc->angle = direction;
	rc->start = (t_xy){start.x * CELL_SIZE, start.y * CELL_SIZE};
	rc->curr_cell = (t_xy){floor(rc->start.x / CELL_SIZE), floor(rc->start.y
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

void	cast_ray(t_var *var, t_xy start, double dir, t_rc *rays)
{
	t_rc	*rc;
	t_xy	end_pos;

	dir = deg2rad(dir);
	rc = rc_init(start, dir);
	while (rc->length < 100)
	{
		ray_goto_next_cell(rc);
		if (detect_walls(var, rc) == 1)
		{
			rc->c = var->map.map[(int)rc->curr_cell.y][(int)rc->curr_cell.x];
			end_pos = draw_line(&var->minimap,
					(t_xy){start.x, start.y},
					dir, rc->length);
			draw_line(&var->minimap,
				(t_xy){start.x * MMAP_SIZE, start.y * MMAP_SIZE},
				dir,
				rc->length * MMAP_SIZE);
			set_texture(rc, end_pos, var);
			break ;
		}
	}
	rc->length *= cos(deg2rad((double)var->map.angle) - (rc->angle));
	rays[0] = *rc;
	free(rc);
}
