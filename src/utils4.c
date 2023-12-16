/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 00:07:49 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/16 13:34:04 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tex_and_color(t_var *var)
{
	if (!(var->tex.n && var->tex.s && var->tex.s && var->tex.s))
		return (0);
	if (!(var->tex.floor && var->tex.ceiling))
		return (0);
	return (1);
}
