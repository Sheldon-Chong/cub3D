/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:46 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/25 18:17:28 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SPACES " \f\v\t\r\n"
# define VALID_CHAR "NSEW01D\f\v\t\r\n "
# define CURRENT_EXIT_CODE 9
# define TEXTURE_SIZE 64
# include "../get_next_line/get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_tex
{
	void				*n;
	void				*s;
	void				*w;
	void				*e;
	int					c[3];
	int					f[3];
}						t_tex;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

typedef struct s_rc
{
	double				dirX;
	double				dirY;
	double				planeX;
	double				planeY;
	double				camX;
	double				rayX;
	double				rayY;
	int					mapX;
	int					mapY;
	double				sideX;
	double				sideY;
	double				deltaX;
	double				deltaY;
	double				perp_dist;
	int					stepX;
	int					stepY;
	int					hit;
	int					side;
	int					start;
	int					end;
	double				wallX;
	int					texX;
	int					texY;
	double				step;
	double				texPos;
	double				moveSpeed;
	double				rotateSpeed;
}						t_rc;

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
	int					loc_x;
	int					loc_y;
	char				dir;
}						t_map;

typedef struct s_img
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_var
{
	t_map				map;
	t_tex				tex;
	t_img				screen;
	t_rc				rc;
	int					max_h;
	int					max_w;
	int					h;
	int					w;
}						t_var;

// init.c
int						init_var(t_var *var);

// error.c
void					error_mes(char *err);

// check.c
int						check_prefix(char *line);
void					check_line(char *line, t_var *var,
							t_map_line **map_lines);
int						check_order(char *path);
int						valid_char(t_map *map_det);
int						no_walls(t_map *map_det);

// parse.c
int						parse_file(char *path, t_var *var);
// int			check_line(char *line, t_var *var);
// int			check_texture(t_tex *tex, t_map *map);
void					parse_tex(char *line, t_var *var);
void					parse_color(char *line, t_var *var);
void					parse_map(char *line, t_map_line **map_lines);

// utils.c
int						ft_isnum(char *n);
void					map_line_add_back(t_map_line **map, t_map_line *new);
int						illegal_map(int x, int y, char **map);

// free.c
void					free_2d(char **arr);

// map.c
void					map_size(t_map_line **map, t_map *map_det);
void					map_insert(t_map_line **map, t_map *map_det);
int						check_map(t_map *map_det);

// rotate.c
void					rotate_north(t_rc *rc);
void					rotate_south(t_rc *rc);
void					rotate_east(t_rc *rc);
void					rotate_west(t_rc *rc);

// draw.c
int						draw_img(t_var *var);

#endif
