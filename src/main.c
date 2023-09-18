/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:42:20 by jakoh             #+#    #+#             */
/*   Updated: 2023/09/18 16:09:13 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_window(t_vars *var)
{
	free_texture(&var->texture);
	free_map(var->map.map);
	mlx_destroy_window(var->screen.mlx, var->screen.win);
	exit(0);
	return (1);
}

void	print_cub(t_vars *vars)
{
	int	i;

	i = -1;
	printf("-----------------CUB3D-----------------\n");
	printf("NO: %s\n", vars->texture.north);
	printf("SO: %s\n", vars->texture.south);
	printf("EA: %s\n", vars->texture.east);
	printf("WE: %s\n", vars->texture.west);
	printf("FLOOR: %i,%i,%i\n", vars->texture.floor[0],
			vars->texture.floor[1],vars->texture.floor[2]);
	printf("CEIL: %i,%i,%i\n", vars->texture.ceiling[0],
			vars->texture.ceiling[1],vars->texture.ceiling[2]);
	printf("--------------------------------------\n");
	while (vars->map.map[++i])
		printf("|%s|\n", vars->map.map[i]);
	printf("--------------------------------------\n");
}

int	main(int ac, char **av)
{
	t_vars	vars;
	
	if (ac != 2)
		exit_with_message("Invalid Number of Arguments.\n", 1);
	init_vars(&vars);
	parse_file(&vars, av[1]);
	mlx_hook(vars.window, 2, 2, key_hook, &vars);
	mlx_hook(vars.window, 17, (1L << 0), exit_on_click, &vars);
	mlx_loop(vars.mlx);
	print_cub(&vars);
	free_texture(&vars.texture);
	free_map(vars.map.map);
	system("leaks cub3d");
	return (2);
}
