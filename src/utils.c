/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:19:33 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/18 19:37:51 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isnum(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (n[i] < '0' || n[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

t_map_line	*map_line_last(t_map_line *line)
{
	if (!line)
		return (0);
	while (line->next && line)
		line = line->next;
	return (line);
}

void	map_line_add_back(t_map_line **map, t_map_line *new)
{
	if (!*map)
		*map = new;
	else
		(map_line_last(*map))->next = new;
}

int	illegal_map(int x, int y, char **map)
{
	if ((x - 1) < 0 || (y - 1) < 0)
		return (1);
	if (!map[y][x + 1] || (!ft_strchr("NSEWD10d", map[y][x + 1])))
		return (1);
	else if (!map[y][x - 1] || (!ft_strchr("NSEWD10d", map[y][x - 1])))
		return (1);
	else if ((int)ft_strlen(map[y + 1]) < x
		|| (!ft_strchr("NSEWD10d", map[y + 1][x])))
		return (1);
	else if ((int)ft_strlen(map[y - 1]) < x
		|| (!ft_strchr("NSEWD10d", map[y - 1][x])))
		return (1);
	else
		return (0);
}
