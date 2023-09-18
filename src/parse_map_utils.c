/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:57:09 by jakoh             #+#    #+#             */
/*   Updated: 2023/09/16 17:17:26 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lstadd_back(t_list_map **lst, t_list_map *new)
{
	t_list_map	*temp;

	if (*lst != NULL)
	{
		temp = *lst;
		while (temp->next != NULL && temp != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

void	strlcpy_custom(char *dst, const char *src, int size)
{
	int	i;

	i = -1;
	while (src[++i] != 0 && i < size)
		dst[i] = src[i];
}

void	malloc_and_fill_map(t_map *map, t_list_map **list_map)
{
	int			i;
	int			len;
	t_list_map	*temp;

	i = -1;
	temp = *list_map;
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	map->map[map->height] = NULL;
	while (++i < map->height)
	{
		map->map[i] = ft_calloc(map->width + 1, sizeof(char));
		ft_memset(map->map[i], ' ', map->width);
		if (i > 0 && i < map->height - 1)
		{
			len = ft_strlen(temp->map_line);
			strlcpy_custom(map->map[i] + 1, temp->map_line, len);
			temp = temp->next;
		}
	}
}
