/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:29:40 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/10 16:29:42 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	place_pixel(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0)
		return (0);
	src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

t_img	*new_img(void *mlx, char *image)
{
	t_img	*tex;

	tex = malloc(sizeof(t_img));
	tex->img = mlx_xpm_file_to_image(mlx, image, &tex->width, &tex->height);
	if (tex->img == NULL)
	{
		free(tex);
		return (NULL);
	}
	tex->addr = mlx_get_data_addr(tex->img, &(tex->bits_per_pixel),
			&(tex->line_length), &(tex->endian));
	return (tex);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && y > 0 && x < 1920 && y < 1080)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)pixel = color;
	}
}
