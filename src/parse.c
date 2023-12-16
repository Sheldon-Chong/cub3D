/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:53:38 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/16 13:32:23 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_tex(char *line, t_var *var)
{
	char	dir;

	if (!check_prefix(line))
		error_mes("Wrong prefix!", var);
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
		error_mes("File not found!", var);
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
	while (char_rgb[i] && i < 3)
	{
		if (ft_isnum(char_rgb[i]) || ft_atoi(char_rgb[i]) < 0
			|| ft_atoi(char_rgb[i]) > 255)
			error_mes("Color Error!", var);
		test[i] = ft_atoi(char_rgb[i]);
		i++;
	}
	if (i != 3)
		error_mes("Error: Please insert colors for RGB\n", var);
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

void	free_map_line(t_map_line *map)
{
	while (map)
	{
		free(map->line);
		free(map);
		map = map->next;
	}
}

int	parse_file(char *path, t_var *var)
{
	char		*line;
	int			fd;
	t_map_line	*map;

	map = NULL;
	if (check_order(path, var) != 0
		|| ft_strcmp(path + ft_strlen(path) - 4, ".cub") != 0)
		error_mes("Error: Unable to open file!", var);
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
	free_map_line(map);
	if (check_map(&var->map, &var->tex, var->screen.mlx) == 1)
		return (1);
	close(fd);
	return (0);
}
