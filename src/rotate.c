/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:41:34 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/25 16:46:26 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_north(t_rc *rc)
{
	rc->dirX = 0;
	rc->dirY = -1;
	rc->planeX = 0.66;
	rc->planeY = 0;
}

void	rotate_south(t_rc *rc)
{
	rc->dirX = 0;
	rc->dirY = 1;
	rc->planeX = -0.66;
	rc->planeY = 0;
}

void	rotate_east(t_rc *rc)
{
	rc->dirX = 1;
	rc->dirY = 0;
	rc->planeX = 0;
	rc->planeY = 0.66;
}

void	rotate_west(t_rc *rc)
{
	rc->dirX = -1;
	rc->dirY = 0;
	rc->planeX = 0;
	rc->planeY = -0.66;
}