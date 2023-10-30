/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:46 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/30 14:18:09 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SPACES " \f\v\t\r\n"
# define VALID_CHAR "NSEW01D\f\v\t\r\n "
# define CURRENT_EXIT_CODE 9
# define TEXTURE_SIZE 64
# define MMAP_SIZE 15
# define COLOR_BLACK 0x00000000
# define COLOR_WHITE 0x00FFFFFF
# define COLOR_RED 0x00FF0000
# define COLOR_GREEN 0x0000FF00
# define COLOR_BLUE 0x000000FF
# define COLOR_YELLOW 0x00FFFF00
# define COLOR_MAGENTA 0x00FF00FF
# define COLOR_CYAN 0x0000FFFF
# define LINUX_W 13
# define LINUX_A 0
# define LINUX_S 1
# define LINUX_D 2
# define LINUX_Q 12
# define LINUX_E 14
# define SCREEN_HEIGHT 1100
# define SCREEN_WIDTH 1200
# define CELL_SIZE 40
# define TEX_HEIGHT 64
# define TEX_WIDTH 64
# define SHOW_2D 0
# define SHOW_3D 1
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>




typedef struct s_xy
{
	double				x;
	double				y;
}						t_xy;

typedef struct s_img
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;
typedef struct s_tex
{
	t_img				*n;
	t_img				*s;
	t_img				*w;
	t_img				*e;
	int					ceiling;
	int					floor;
}						t_tex;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

// typedef struct s_rc
// {
// 	double				dir_x;
// 	double				dir_y;
// 	double				plane_x;
// 	double				plane_y;
// 	double				cam;
// 	double				ray_x;
// 	double				ray_y;
// 	int					map_x;
// 	int					map_y;
// 	double				side_x;
// 	double				side_y;
// 	double				delta_x;
// 	double				delta_y;
// 	double				perp_dist;
// 	int					step_x;
// 	int					step_y;
// 	int					hit;
// 	int					side;
// 	int					start;
// 	int					end;
// 	double				wall;
// 	int					tex_x;
// 	int					tex_y;
// 	double				step;
// 	double				tex_pos;
// 	double				move;
// 	double				rotate;
// 	int					line_height;
// }						t_rc;

typedef struct s_rc
{
	t_xy				dir;
	t_xy				start;
	t_xy				current_cell;
	t_xy				cell_step;
	t_xy				unit_length;
	t_xy				distance;
	float				length;
	int					color;
	int					xy;
	int					texture_column;
	float				angle;
	t_img				*texture;
}						t_rc;

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
	double				loc_x;
	double				loc_y;
	char				dir;
	int					angle;
}						t_map;

typedef struct s_var
{
	t_map				map;
	t_tex				tex;
	t_img				screen;
	t_img				minimap;
	t_img				ui;
	t_img				heart;
	t_img				player_pov;
	t_rc				rc;
	int					*sec;
	int					max_h;
	int					max_w;
	int					h;
	int					w;
	int					mouse_x;
	int					mouse_y;
}						t_var;

// init.c
t_rc					*rc_init(t_xy start, double direction);
int						init_var(t_var *var);
void					rotate(t_var *var, char dir);

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
int						rgb(int r, int g, int b);

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
int						draw_img(void *params);

// texture.c
// void					draw_tex(t_var *var, int x);
void					put_pixel(t_img *img, int x, int y, int color);

//utils2.c
double					deg2rad(double num);
t_xy					angle_to_vector(double angle);
t_xy					op(t_xy xy1, t_xy xy2, char op);
void					draw_rect(t_img *image, t_xy start, t_xy wh, int color);
int						get_color(t_img *img, int x, int y);

void					decide_direction(t_rc *rc);
int						ray_goto_next_cell(t_rc *rc);
void					set_ray_textures(char c, t_rc *rc,
							t_xy end_pos, t_var *var);
t_rc					*rc_init(t_xy start, double direction);
void					cast_ray(t_var *var, t_xy start,
							double dir, t_rc *rays);
t_rc					*cast_rays(t_var *var, int ray_count);
int						draw_img(void *params);
t_xy					draw_line_dir(t_img *img, t_xy start, double direction,
							double distance, int color);
void					place_pixel(t_img *image, int x, int y, int color);
t_img					*new_img(void *mlx, char *image);


#endif
