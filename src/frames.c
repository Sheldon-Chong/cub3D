/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:22:18 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/11/11 23:49:21 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	insert_frames(t_var *var)
{
	var->frames = malloc(8 * sizeof(t_img *));
	var->frames[0] = (new_img(var->screen.mlx, "shotgun/1.xpm"));
	var->frames[1] = (new_img(var->screen.mlx, "shotgun/2.xpm"));
	var->frames[2] = (new_img(var->screen.mlx, "shotgun/3.xpm"));
	var->frames[3] = (new_img(var->screen.mlx, "shotgun/4.xpm"));
	var->frames[4] = (new_img(var->screen.mlx, "shotgun/5.xpm"));
	var->frames[5] = (new_img(var->screen.mlx, "shotgun/6.xpm"));
	var->frames[6] = (new_img(var->screen.mlx, "shotgun/7.xpm"));
	var->frames[7] = (new_img(var->screen.mlx, "shotgun/8.xpm"));
	var->player_pov = var->frames[0];
	var->heart = (new_img(var->screen.mlx, "cross.xpm"));
}
