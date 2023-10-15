#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cube3d.h"

void move_player(int keycode, t_game *frame, t_xy direction_vec)
{
	t_xy new_pos = op(frame->player->pos, direction_vec, '+');
	if(frame->map[(int)(new_pos.y)][(int)(new_pos.x)] == '1')
		printf("error\n");
	else	
		frame->player->pos = new_pos;
}

int	handle_keypress(int keycode, t_game *frame)
{
	t_game *data = frame;
	double amount = 0.1;

	t_xy increase;

	t_player *player = data->player;

	if (keycode == LINUX_W)
		move_player(keycode, frame, op(angleToVector(deg2rad(player->angle)), (t_xy){amount,amount}, '*'));
	if (keycode == LINUX_A)
		move_player(keycode, frame, op(angleToVector(deg2rad(player->angle-90)), (t_xy){amount,amount}, '*'));
	if (keycode == LINUX_S)
		move_player(keycode, frame, op(angleToVector(deg2rad(player->angle+180)), (t_xy){amount,amount}, '*'));
	if (keycode == LINUX_D)
		move_player(keycode, frame, op(angleToVector(deg2rad(player->angle+90)), (t_xy){amount,amount}, '*'));
	if (keycode == LINUX_E)
		player->angle += 5;
	if (keycode == LINUX_Q)
		player->angle -= 5;
	if (keycode == 49)
		player->val += 1;
	if (keycode == 51) 
		player->val -= 1;
	printf("%d \n", keycode);
	return (0);
}



//RAY ======================================================

t_ray *ray_init(t_xy start, double direction)
{
	t_ray	*ray;
	ray = malloc(sizeof(t_ray));

	ray->dir = (t_xy){cos(direction), sin(direction)};
	ray->start = (t_xy){start.x * CELL_SIZE, start.y * CELL_SIZE};
	ray->current_cell = (t_xy){floor(ray->start.x / CELL_SIZE), floor(ray->start.y / CELL_SIZE)};
	ray->cell_step = (t_xy){0,0};
	ray->unit_length.x = sqrt(1.0 + (ray->dir.y/ray->dir.x) * (ray->dir.y/ray->dir.x));
	ray->unit_length.y = sqrt(1.0 + (ray->dir.x/ray->dir.y) * (ray->dir.x/ray->dir.y));
	ray->distance = (t_xy){0,0};
	ray->length = 0;

	return(ray);
}

t_ray *decide_direction(t_ray *ray)
{
	if (0 > ray->dir.x)
	{
		ray->cell_step.x = -1;
		ray->distance.x = ray->unit_length.x * (ray->start.x / CELL_SIZE - ray->current_cell.x);	
	}
	else if (0 < ray->dir.x)
	{
		ray->cell_step.x = 1;
		ray->distance.x = ray->unit_length.x * ((1 + ray->current_cell.x) - ray->start.x / CELL_SIZE);
	}
	if(0 > ray->dir.y)
	{
		ray->cell_step.y = -1;
		ray->distance.y = ray->unit_length.y * (ray->start.y / CELL_SIZE - ray->current_cell.y);
	}
	else if (0 < ray->dir.y)
	{
		ray->cell_step.y = 1;
		ray->distance.y = ray->unit_length.y * ((1+ ray->current_cell.y) - ray->start.y / CELL_SIZE);
	}
	return ray;
}

int ray_goto_next_cell(t_game *game, t_ray *ray)
{
	int corner_collision = 0;
	if(ray->distance.x < ray->distance.y)
	{
		ray->length = ray->distance.x;
		ray->distance.x += ray->unit_length.x;
		ray->current_cell.x += ray->cell_step.x;
		ray->xy = 1;
	}
	else if(ray->distance.x > ray->distance.y)
	{
		ray->length = ray->distance.y;
		ray->distance.y += ray->unit_length.y;
		ray->current_cell.y += ray->cell_step.y;
		ray->xy = 0;
	}
	else
	{
		corner_collision = 1;
		ray->length = ray->distance.x;
		ray->distance.x += ray->unit_length.x;
		ray->distance.y += ray->unit_length.y;
		ray->current_cell.x += ray->cell_step.x;
		ray->current_cell.y += ray->cell_step.y;
	}
	return(corner_collision);
}

//RAY ======================================================

t_xy cell(t_xy pos)
{
	return((t_xy){pos.x * CELL_SIZE, pos.y * CELL_SIZE});
}

void set_ray_textures(char c, t_ray *ray, t_xy end_pos, t_game *game)
{
	double dif;
	if(c == 'N')
	{
		dif = end_pos.x - ray->current_cell.x;
		ray->texture = game->north;
	}
	else if( c == 'S')
	{
		dif = end_pos.x - ray->current_cell.x;
		ray->texture = game->south;
	}
	else if(c == 'E')
	{
		dif = end_pos.y - ray->current_cell.y;
		ray->texture = game->east;
	}
	else if(c == 'W')
	{
		dif = end_pos.y - ray->current_cell.y;
		ray->texture = game->west;
	}
	ray->texture_column = (int)(dif * ray->texture->width);
}

void cast_ray(t_game *game, t_xy start, double direction, t_ray *rays)
{	
	int corner_collision;
	direction = deg2rad(direction)/1;
	t_ray *ray;
	
	ray = ray_init(start, direction);	
	t_xy starting_cell =  (t_xy){floor(ray->start.x / CELL_SIZE), floor(ray->start.y / CELL_SIZE)};
	decide_direction(ray);
	while(ray->length < 10)
	{
		int corner_collision = ray_goto_next_cell(game, ray);
		if(ray->current_cell.x > 0 && ray->current_cell.y > 0 && ray->current_cell.x < 30 && ray->current_cell.y < 30)
		{
			if (game->map[(int)ray->current_cell.y][(int)ray->current_cell.x] == '1')
			{
				t_xy end_pos = draw_line_dir(game->mlx, game->mlx_win, (t_xy){start.x, start.y}, direction, ray->length, COLOR_CYAN);
				if(ray->xy == 0)
					set_ray_textures("SN"[(ray->dir.y > 0)], ray, end_pos, game);
				if(ray->xy == 1)
					set_ray_textures("WE"[(ray->dir.x > 0)], ray, end_pos, game);
				//draw_rectquare(game->mlx, game->mlx_win, cell(ray->current_cell), cell((t_xy){0.2,0.2}), COLOR_GREEN);
				break;
			}
			else if (1 == corner_collision && game->map[(int)ray->current_cell.x][(int)ray->current_cell.y] == '1')
				break;
		}
	}
	if(ray->length > 10)
		ray->length = 10;
	if (SHOW_LINE && SHOW_2D && (int)(ray) %2 == 0)
		draw_line_dir(game->mlx, game->mlx_win, cell((t_xy){start.x, start.y}), direction, ray->length * CELL_SIZE, COLOR_CYAN);
	if(ray->length == 10)
		ray->length = 0;
	rays[0] = *ray;
}

//PLAYER ======================================================


int render_2D_View(t_game *game)
{
	void		*mlx;
	void		*mlx_win;
	t_player	*player;

	mlx = game->mlx;
	mlx_win = game->mlx_win;
	player = game->player;
	draw_grid(mlx, mlx_win, (t_xy){30, 30}, cell((t_xy){1, 1}), game->map);
	draw_rectquare(mlx, mlx_win, cell(op(player->pos, (t_xy){}, 'i')), cell((t_xy){1, 1}), COLOR_YELLOW);
	draw_rectquare(mlx, mlx_win, cell(player->pos),(t_xy){10, 10}, COLOR_GREEN);
	draw_line_dir(mlx, mlx_win, cell(player->pos), deg2rad(player->angle), 5 * CELL_SIZE, COLOR_BLUE);
	return 1;	
}

int render_3d_view(t_game *game, t_ray *rays, int ray_count)
{
	int i;

	t_player *player = game->player;

	draw_rect(game->frame, (t_xy){0, 0}, (t_xy){SCREEN_WIDTH, 300}, COLOR_BLUE);
	draw_rect(game->frame, (t_xy){0, 300}, (t_xy){SCREEN_WIDTH, 299}, COLOR_BLACK);
	float projection_distance = 0.5f* CELL_SIZE / tan(deg2rad(0.5f * 58.75f));
	
	i = -1;
	while(++i < ray_count)
	{
		float ray_direction = player->fov * (floor(0.5f * SCREEN_WIDTH) - i) / (SCREEN_WIDTH - 1);
		float ray_projection_position = 0.5f * tan(deg2rad(ray_direction)) / tan(deg2rad(0.5f* player->fov));
		
		short current_column = round(SCREEN_WIDTH * (0.5f - ray_projection_position));
		short next_column = SCREEN_WIDTH;

		if(i < SCREEN_WIDTH - 1)
		{
			float next_ray_direction = player->fov * (floor(0.5f* SCREEN_WIDTH) - 1 - i) / (SCREEN_WIDTH - 1);

			ray_projection_position = 0.5f * tan(deg2rad(next_ray_direction)) / tan(deg2rad(0.5f* player->fov));
			next_column = round(SCREEN_WIDTH * (0.5f - ray_projection_position));
		}
		if(rays[i].length > 0)
		{
			int i2 = -1;
			t_texture texture = *(rays[i].texture);
			
			while(++i2 < texture.height)
			{
				float shape_height = round(SCREEN_HEIGHT * projection_distance /( (rays[i].length * 40) * cos(deg2rad(ray_direction))));
				t_xy start = (t_xy){current_column, ((SCREEN_HEIGHT - shape_height)) / 2 + (shape_height * ((double)(i2)/(texture.height)))};
				int color = rays[i].color;
				if(rays[i].texture)
					color = get_mlx_pixel_color(texture.img, texture.width - rays[i].texture_column - 1, i2);
				
				if(start.x < SCREEN_WIDTH && start.x > 0)
					draw_rect(game->frame, start, (t_xy){next_column - current_column, (shape_height * (1)/(double)(texture.height))}, color);
			}
		}
	} 
	return 1;
}

int render_next_frame(void *param)
{
	t_game	*data;
	int		ray_count;
	t_ray	*rays;
	int		i;
	
	ray_count = SCREEN_WIDTH;
	data = (t_game*)param;
	(*(data->sec))++;
	if (*(data->sec) > 300)
	{
		if(SHOW_2D)
			render_2D_View(data);
		rays = malloc(sizeof(t_ray) * (ray_count + 1));
		i = -1;
		while(++i < ray_count)
			cast_ray(data, data->player->pos, (data->player->angle) + (float)(i - (ray_count * 0.5)) / 10, rays + i);
		if(SHOW3D)
		{
			render_3d_view(data, rays, ray_count);
			free(rays);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame->img, 0,0);
		}
		*(data->sec) = 0;
	}
	return 1;
}


t_data	*put_img(char *image, void *mlx)
{
	int		img_width;
	int		img_height;
	t_data	*img;

	img = malloc(sizeof(t_data));
	img->img = mlx_xpm_file_to_image(mlx, image, &img_width, &img_height);
	printf("%s | %p, %p\n", image, img, img->img);
	if (img->img == NULL)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	return (img);
}



int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	int			sec;
	t_player	player;
	char		**map;

	// init mlx
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");

	//init map
	map = init_2d_array(40, 40);
	print_array(map);

	//init player
	player = (t_player){(t_xy){5.5, 5.5}};
	player.fov = 66.5;	
	
	//init game information
	sec = 0;
	t_data *frame_img = new_img(mlx, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
	t_game game = (t_game){mlx, mlx_win, &sec, map, &player, frame_img};
	
	//init textures
	t_texture *north = malloc(sizeof(t_texture));
	t_texture *south = malloc(sizeof(t_texture));
	t_texture *east = malloc(sizeof(t_texture));
	t_texture *west = malloc(sizeof(t_texture));
	
	*north = (t_texture){put_img("wall_6_4.xpm", mlx), 64, 64};
	*south = (t_texture){put_img("wall_1_1.xpm", mlx), 64, 64};
	*east = (t_texture){put_img("wall_1_3.xpm", mlx), 64, 64};
	*west = (t_texture){put_img("wall_1_4.xpm", mlx), 64, 64};
	
	game.north = north;
	game.south = south;
	game.east = east;
	game.west = west;

	mlx_hook(mlx_win, 2, 1L << 0, handle_keypress, &game);
	mlx_loop_hook(mlx, render_next_frame, &game);
	mlx_loop(mlx);
}