/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:53:38 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/18 17:24:01 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*put_img(void *mlx, char *image)
{
	t_img	*tex;
	int		w;
	int		h;

	tex = malloc(sizeof(t_img));
	tex->img = mlx_xpm_file_to_image(mlx, image, &w, &h);
	if (tex->img == NULL)
	{
		free(tex);
		return (NULL);
	}
	tex->addr = mlx_get_data_addr(tex->img, &(tex->bits_per_pixel),
			&(tex->line_length), &(tex->endian));
	return (tex);
}

void	parse_tex(char *line, t_var *var)
{
	char	dir;

	if (!check_prefix(line))
		error_mes("Wrong prefix!");
	dir = line[0];
	line = ft_strchr(line, '.');
	if (dir == 'N' && !var->tex.n)
		var->tex.n = put_img(var->screen.mlx, line);
	else if (dir == 'S' && !var->tex.s)
		var->tex.s = put_img(var->screen.mlx, line);
	else if (dir == 'W' && !var->tex.w)
		var->tex.w = put_img(var->screen.mlx, line);
	else if (dir == 'E' && !var->tex.e)
		var->tex.e = put_img(var->screen.mlx, line);
	if ((dir == 'N' && !var->tex.n) || (dir == 'S' && !var->tex.s)
		|| (dir == 'W' && !var->tex.w) || (dir == 'E' && !var->tex.e))
		error_mes("File not found!");
}

void	parse_color(char *line, t_var *var)
{
	int		i;
	char	**rgb;
	char	dir;

	i = 0;
	dir = line[0];
	line = ft_strchr(line, ' ') + 1;
	rgb = ft_split(line, ',');
	while (rgb[i])
	{
		if (ft_isnum(rgb[i]) || ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			error_mes("Color Error!");
		if (dir == 'F')
			var->tex.f[i] = ft_atoi(rgb[i]);
		else if (dir == 'C')
			var->tex.c[i] = ft_atoi(rgb[i]);
		i++;
	}
	free_2d(rgb);
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
