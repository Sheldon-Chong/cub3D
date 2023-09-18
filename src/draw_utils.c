/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:33:46 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/18 15:56:18 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pix_draw(t_vars *var, int x, int y, int color)
{
	char	*pix;

	if (y < 0 || y > var->max_height - 1 || x < 0 || x > var->max_width - 1)
		return ;
	pix = var->screen.addr + (y * var->screen.line_length + x * (var->screen.bpp
				/ 8));
	*(unsigned int *)pix = color;
}

int	path_to_img(t_img *img, char *path)
{
	img->mlx = mlx_init();
	if (!(img->mlx))
		return (1);
	img->img = mlx_xpm_file_to_image(img->mlx, path, &img->width, &img->height);
	if (!(img->img))
	{
		printf("%s does not exist!\n", path);
		return (1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
	return (0);
}

int	set_img(t_vars *var)
{
	if (path_to_img(&var->tex_img.n, var->texture.north)
		|| path_to_img(&var->tex_img.s, var->texture.south)
		|| path_to_img(&var->tex_img.e, var->texture.east)
		|| path_to_img(&var->tex_img.w, var->texture.west))
		return (1);
	free(var->texture.north);
	free(var->texture.east);
	free(var->texture.south);
	free(var->texture.west);
	return (0);
}

void	put_pix(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
