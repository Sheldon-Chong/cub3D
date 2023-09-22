/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:44:40 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/22 21:27:25 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 2)
		error_mes("Invalid Number of Arguments.\n");
	if (init_var(&var) || parse_file(argv[1], &var))
		return (1);
	return (0);
}