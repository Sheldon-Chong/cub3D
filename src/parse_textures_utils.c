/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:07:32 by jakoh             #+#    #+#             */
/*   Updated: 2023/09/18 15:53:50 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Returns 1 if theres missing Texture, 0 if all textures are found
 * 
 * @param texture 
 * @return int
 */
int	miss_textures(t_texture *texture)
{
	if (!texture->north || !texture->south || !texture->east || !texture->west
		|| !texture->floor || !texture->ceiling)
		return (1);
	return (0);
}

/**
 * @brief Check if string only contains digits
 * 
 * @param str 
 * @return int 
 */
int	only_digits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}
