/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:40:45 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/07 13:03:42 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_mes(char *err, t_var *var)
{
	ft_putstr_fd(err, 2);
	if (var->map.map)
		free_frames(var);
	exit(2);
}

int	exit_program(t_var *var)
{
	free_frames(var);
	exit(0);
	return (1);
}
