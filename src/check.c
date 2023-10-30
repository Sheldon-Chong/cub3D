/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:29:20 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/30 14:40:46 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_prefix(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		line = ft_strtrim(line + 2, SPACES);
		if (ft_strncmp(line, "./", 2) == 0)
			return (1);
	}
	return (0);
}

void	check_line(char *line, t_var *var, t_map_line **map_lines)
{
	char	*tmp;

	tmp = line;
	line = ft_strtrim(line, SPACES);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
		parse_tex(line, var);
	else if ((ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0))
		parse_color(line, var);
	else if (line[0] == '1')
		parse_map(tmp, map_lines);
	else
		return ;
}

int	check_order(char *path)
{
	char	*line;
	char	first[7];
	int		i;
	int		fd;

	i = -1;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		line = ft_strtrim(line, SPACES);
		if (line[0] && ++i < 7)
			first[i] = line[0];
		line = get_next_line(fd);
	}
	if (ft_strncmp(first, "NSWEFC1", 7))
		error_mes("Wrong order!");
	return (0);
}

int	valid_char(t_map *map_det)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = -1;
	while (map_det->map[++j])
	{
		i = -1;
		while (map_det->map[j][++i])
		{
			if (!ft_strchr(VALID_CHAR, map_det->map[j][i]))
				return (1);
			else if (ft_strchr("NSEW", map_det->map[j][i]))
			{
				map_det->dir = map_det->map[j][i];
				map_det->pos.x = i;
				map_det->pos.y = j;
				count++;
			}
		}
	}
	if (count != 1)
		return (1);
	return (0);
}

int	no_walls(t_map *map_det)
{
	int illegal;
	int x;
	int y;

	illegal = 0;
	y = -1;
	while (map_det->map[++y])
	{
		x = -1;
		while (map_det->map[y][++x])
		{
			if (map_det->map[y][x] == '0' || ft_strchr("NSEWD",
					map_det->map[y][x]))
			{
				if (illegal_map(x, y, map_det->map) == 1)
					illegal = 1;
			}
		}
	}
	if (illegal == 1)
		return (1);
	return (0);
}