/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:29:20 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/10 01:54:01 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_prefix(char *line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		tmp = ft_strtrim(line + 2, SPACES);
		if (ft_strncmp(tmp, "./", 2) == 0)
		{
			free(tmp);
			return (1);
		}
	}
	free(tmp);
	return (0);
}

void	check_line(char *line, t_var *var, t_map_line **map_lines)
{
	char	*tmp;
	char	*tmp2;

	tmp = line;
	tmp2 = ft_strtrim(line, SPACES);
	if (tmp2[0] == 'N' || tmp2[0] == 'S' || tmp2[0] == 'E' || tmp2[0] == 'W')
	{
		parse_tex(tmp2, var);
		free(tmp2);
	}
	else if ((ft_strncmp(tmp2, "F ", 2) == 0 || ft_strncmp(tmp2, "C ", 2) == 0))
	{
		parse_color(tmp2, var);
		free(tmp2);
	}
	else if (tmp2[0] == '1')
	{
		parse_map(tmp, map_lines);
		free(tmp2);
	}
	else
	{
		free(tmp2);
		return ;
	}
}

int	check_order(char *path, t_var *var)
{
	char	*line;
	char	*tmp;
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
		tmp = ft_strtrim(line, SPACES);
		if (tmp[0] && ++i < 7)
			first[i] = tmp[0];
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	if (ft_strncmp(first, "NSWEFC1", 7))
		error_mes("Wrong order!", var);
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
			if (map_det->map[y][x] == '0' || ft_strchr("NSEWDd",
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