/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:40:45 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/12/07 16:18:46 by nwai-kea         ###   ########.fr       */
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

void	error_mes_argc(char *err)
{
	ft_putstr_fd(err, 2);
	exit(2);
}

int	exit_program(t_var *var)
{
	free_frames(var);
	exit(0);
	return (1);
}
