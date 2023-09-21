/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:34:49 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/22 02:03:34 by nwai-kea         ###   ########.fr       */
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
		map_det->height++;
		line = line->next;
	}
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
		map_det->map[i] = (char *)malloc(sizeof(char) * (map_det->width + 1));
		map_det->map[i] = line->line;
		line = line->next;
		i++;
	}
	map_det->map[i] = NULL;
}

int		check_map(t_map *map_det)
{
	if (valid_char(map_det))
		return (1);
	if (no_walls(map_det))
		return (1);
	return (0);
}