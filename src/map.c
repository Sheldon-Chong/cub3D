/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:34:49 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/18 19:27:46 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_size(t_map_line **map, t_map *map_det)
{
	t_map_line	*line;

	map_det->height = 0;
	line = *map;
	map_det->width = 0;
	while (line)
	{
		if ((int)(ft_strlen(line->line) - 1) > map_det->width)
			map_det->width = ft_strlen(line->line);
		if (ft_strlen(line->line) != 1)
			map_det->height++;
		line = line->next;
	}
	map_det->width -= 1;
}

void	map_insert(t_map_line **map, t_map *map_det)
{
	t_map_line	*line;
	int			i;

	line = *map;
	i = 0;
	map_det->map = (char **)malloc(sizeof(char *) * (map_det->height + 1));
	while (i < map_det->height)
	{
		if (ft_strlen(line->line) > 1)
		{
			map_det->map[i] = ft_strdup(line->line);
			i++;
		}
		else if (ft_strlen(line->line) == 1
			&& ft_strlen(line->next->line) != 1 && i != 0)
			error_mes_argc("Error: Invalid map (Spacing)\n");
		line = line->next;
	}
	map_det->map[i] = NULL;
}

int	check_doors(t_map *map_det, t_tex *tex, void *mlx)
{
	int	x;
	int	y;
	int	doors;

	y = -1;
	doors = 0;
	while (map_det->map[++y])
	{
		x = -1;
		while (map_det->map[y][++x])
		{
			if (map_det->map[y][x] == 'D' || map_det->map[y][x] == 'd')
				doors += 1;
		}
	}
	if (doors > 0 && !tex->door && !tex->door_open)
	{
		tex->door = new_img(mlx, "./texture/door.xpm");
		tex->door_open = new_img(mlx, "./texture/door_open.xpm");
	}
	if (doors > 0 && (!tex->door || !tex->door_open))
		return (1);
	return (0);
}

int	check_map(t_map *map_det, t_tex *tex, void *mlx)
{
	if (valid_char(map_det))
		return (1);
	if (no_walls(map_det))
		return (1);
	if (check_doors(map_det, tex, mlx))
		return (1);
	return (0);
}
