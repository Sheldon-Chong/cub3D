/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:43:46 by jakoh             #+#    #+#             */
/*   Updated: 2023/09/18 16:00:00 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief check if path is accessable and assign texture to struct variable
 * 
 * @param check 
 * @param texture 
 */
void	check_texture_path(t_vars *vars, void **check, char *path)
{
	int	tx_size;
	
	tx_size = 64;
	*check = mlx_xpm_file_to_image(vars->mlx, path, &tx_size, &tx_size);
	free(path);
	if (*check == NULL)
		exit_with_message("Error: Invalid Texture\n", 6);
		
}

/**
 * @brief check if rgb is valid and assign int rgb if color is valid
 * 
 * @param check 
 * @param texture 
 */
void	check_rgb(void **check, char *texture)
{
	char	**store;
	int		i;
	int		error;

	error = 0;
	i = -1;
	store = ft_split(texture, ',');
	*check = ft_calloc(3, sizeof(int));
	while (store[++i])
	{
		if (i > 2)
			error++;
		else if (only_digits(store[i]) && error == 0)
			((int *)*check)[i] = ft_atoi(store[i]);
		else
			error++;
		if (((int *)*check)[i] > 255)
			error++;
	}
	free(texture);
	free_map(store);
	if (error || i != 3)
		exit_with_message("Error: Invalid Color\n", 6);
}

void	check_textures(t_vars *vars, void **check, char *get_path, char c)
{
	if (c == 'F' || c == 'C')
		check_rgb(check, get_path);
	else
		check_texture_path(vars, check, get_path);
}

/**
 * @brief Check if texture has been found \n
 * 		  and append texture path if not. \n
 * free_texture(tex);
 * free(trimmed);
 * if (get_path)
 * 		free(get_path);
 * 
 * @param tex texture struct
 * @param check pointer to specific texture to append
 * @param trimmed trimmed string from parent
 * @param c first character of trimmed string
 */
void	check_n_append(t_vars *vars, void **check, char *trimmed, char c)
{
	int		error;
	char	*get_path;

	error = 0;
	get_path = NULL;
	if (*check != NULL)
		error = 5;
	else if (c == 'F' || c == 'C')
		get_path = ft_strtrim(trimmed + 1, SPACES);
	else
		get_path = ft_strtrim(trimmed + 2, SPACES);
	if (error == 0 && get_path != NULL && *get_path != '\0')
		check_textures(vars, check, get_path, c);
	else
		exit_with_message("Error: Invalid Textures\n", 6);
}

/**
 * @brief Get the texture object
 * 
 * @param vars variables
 * @param tx texture
 * @param line line read
 * @param fc first character
 */
void	get_texture(t_vars *vars, t_texture *tx, char *line, char fc)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, SPACES);
	if (trimmed != NULL && *trimmed != '\0')
	{
		if (fc == 'N')
			check_n_append(vars, (void **)&tx->north, trimmed, fc);
		else if (fc == 'S')
			check_n_append(vars, (void **)&tx->south, trimmed, fc);
		else if (fc == 'E')
			check_n_append(vars, (void **)&tx->east, trimmed, fc);
		else if (fc == 'W')
			check_n_append(vars, (void **)&tx->west, trimmed, fc);
		else if (fc == 'F')
			check_n_append(vars, (void **)&tx->floor, trimmed, fc);
		else if (fc == 'C')
			check_n_append(vars, (void **)&tx->ceiling, trimmed, fc);
	}
	free(trimmed);
}
