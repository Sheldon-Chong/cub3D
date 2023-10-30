/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:53:38 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/30 14:34:32 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_tex(char *line, t_var *var)
{
	char	dir;

	if (!check_prefix(line))
		error_mes("Wrong prefix!");
	dir = line[0];
	line = ft_strchr(line, '.');
	if (dir == 'N' && !var->tex.n)
		var->tex.n = new_img(var->screen.mlx, line);
	else if (dir == 'S' && !var->tex.s)
		var->tex.s = new_img(var->screen.mlx, line);
	else if (dir == 'W' && !var->tex.w)
		var->tex.w = new_img(var->screen.mlx, line);
	else if (dir == 'E' && !var->tex.e)
		var->tex.e = new_img(var->screen.mlx, line);
	if ((dir == 'N' && !var->tex.n) || (dir == 'S' && !var->tex.s)
		|| (dir == 'W' && !var->tex.w) || (dir == 'E' && !var->tex.e))
		error_mes("File not found!");
}

void	parse_color(char *line, t_var *var)
{
	int		i;
	char	**char_rgb;
	char	dir;
	int		test[3];

	i = 0;
	dir = line[0];
	line = ft_strchr(line, ' ') + 1;
	char_rgb = ft_split(line, ',');
	while (char_rgb[i])
	{
		if (ft_isnum(char_rgb[i]) || ft_atoi(char_rgb[i]) < 0
			|| ft_atoi(char_rgb[i]) > 255)
			error_mes("Color Error!");
		test[i] = ft_atoi(char_rgb[i]);
		i++;
	}
	if (dir == 'F')
		var->tex.floor = rgb(test[0], test[1], test[2]);
	if (dir == 'C')
		var->tex.ceiling = rgb(test[0], test[1], test[2]);
	free_2d(char_rgb);
}

void	parse_map(char *line, t_map_line **map_lines)
{
	t_map_line	*road;

	road = (t_map_line *)malloc(sizeof(t_map_line));
	road->line = ft_strdup(line);
	road->next = NULL;
	map_line_add_back(map_lines, road);
}

int	parse_file(char *path, t_var *var)
{
	char		*line;
	int			fd;
	t_map_line	*map;

	map = NULL;
	if (check_order(path) != 0)
		error_mes("Unable to open file!");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		check_line(line, var, &map);
		free(line);
		line = get_next_line(fd);
	}
	map_size(&map, &var->map);
	map_insert(&map, &var->map);
	if (check_map(&var->map))
		return (1);
	close(fd);
	return (0);
}
