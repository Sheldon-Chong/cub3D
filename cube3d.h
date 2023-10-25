#define COLOR_BLACK     0x00000000
#define COLOR_WHITE     0x00FFFFFF
#define COLOR_RED       0x00FF0000
#define COLOR_GREEN     0x0000FF00
#define COLOR_BLUE      0x000000FF
#define COLOR_YELLOW    0x00FFFF00
#define COLOR_MAGENTA   0x00FF00FF
#define COLOR_CYAN      0x0000FFFF

#define SHOW_2D 0
#define SHOW_LINE 1
#define SHOW_BOX 0
#define SHOW_EDGE 0

#define SHOW3D 1
#define LINUX_W 13
#define LINUX_A 0
#define LINUX_S 1
#define LINUX_D 2
#define LINUX_Q 12
#define LINUX_E 14

// #define LINUX_W 13
// #define LINUX_A 0
// #define LINUX_S 1
// #define LINUX_D 2
// #define LINUX_Q 12
// #define LINUX_E 14

#define CELL_SIZE 40
#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 100

#define CG     0x0000FF00
#define CB      0x000000FF
#define CY    0x00FFFF00
#define CYD (CY | 0x80000000)

int north[16][16] = {
	{CY,CG,CY,CB,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CY},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CG,CG,CG,CY,CG,CG,CY,CG,CG,CY,CY,CY,CG,CG,CG, CG},
	{CG,CG,CG,CY,CG,CG,CY,CG,CG,CG,CY,CG,CG,CG,CG, CG},
	{CG,CG,CG,CY,CG,CG,CY,CG,CG,CG,CY,CG,CG,CG,CG, CG},
	{CG,CG,CG,CY,CY,CY,CY,CG,CG,CG,CY,CG,CG,CG,CG, CG},
	{CG,CG,CG,CY,CG,CG,CY,CG,CG,CG,CY,CG,CG,CG,CG, CG},
	{CG,CG,CG,CY,CG,CG,CY,CG,CG,CG,CY,CG,CG,CG,CG, CG},
	{CG,CG,CG,CY,CG,CG,CY,CG,CG,CY,CY,CY,CG,CG,CG, CG},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CG},
	{CY,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG,CG, CY},
};

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_xy
{
	double x;
	double y;
} t_xy;

typedef struct	s_player 
{
	t_xy pos;
	int angle;
	int zoom;
	float fov;
	double val;
} t_player;


typedef struct s_texture
{
	t_data *img;
	int width;
	int height;
} t_texture;

typedef struct	s_game
{
	void *mlx;
	void *mlx_win;
	int *sec;
	char **map;
	t_player *player;
	t_data *frame;
	t_texture *north;
	t_texture *south;
	t_texture *east;
	t_texture *west;
} t_game;


typedef struct s_ray
{
	t_xy dir;
	t_xy start;
	t_xy current_cell;
	t_xy cell_step;
	t_xy unit_length;
	t_xy distance;
	float length;
	int color;
	int xy;
	t_texture *texture;
	int texture_column;
} t_ray;

void print_array(char **array)
{
	int sec = -1;
	while(array[++sec])
		printf("%s\n", array[sec]);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if(x < 0 || y < 0)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int get_mlx_pixel_color(t_data *data, int x, int y)
{
    if (x < 0 || y < 0)
        return 0; // Return a default color when out of bounds

    char * src = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return *(unsigned int*)src;
}

void draw_rectquare(void *mlx, void *mlx_win, t_xy start, t_xy wh, int color)
{
	int y = -1;
	int x;
	while(++y < wh.y)
	{
		x = -1;
		while(++x < wh.x)
			mlx_pixel_put(mlx, mlx_win, x+start.x, y + start.y, color);
	}
}

int randomOneOrZero()
{
    return rand() % 2;  // Generates 0 or 1
}

void draw_rect(t_data *image, t_xy start, t_xy wh, int color)
{
	int y = -1;
	int x;

	while(++y < wh.y)
	{
		x = -1;
		while(++x < wh.x)
		{
			if(x + start.x > 0 && x + start.x < image->line_length && y + start.y <SCREEN_HEIGHT - 2 && y + start.y > 0)
			my_mlx_pixel_put(image, x + start.x,y +start.y, color);
			if( y + start.y > SCREEN_HEIGHT || start.x + x > SCREEN_WIDTH)
				break;
		}
	}
}

void draw_rect2(t_data *image, t_xy start, t_xy end, int color)
{
	while(start.y < end.y)
	{
		start.x = -1;
		while(start.x < end.x)
		{
			if(start.x < image->line_length && start.y < SCREEN_HEIGHT - 2 && start.y > 0)
				my_mlx_pixel_put(image, start.x, start.y, color);
			start.x ++;
		}
			
		start.y ++;
	}
}

void draw_grid(void *mlx, void* mlx_win, t_xy cell_wh, t_xy gap_wh, char **map)
{
	int y = -1;
	int x;
	while(++y < cell_wh.y)
	{
		x = -1;
		while(++x < cell_wh.x)	
		{
			draw_rectquare(mlx, mlx_win, (t_xy){x * gap_wh.x, y * gap_wh.y}, (t_xy){2, 2}, COLOR_RED);
			if(map[y][x] == '1')
				draw_rectquare(mlx, mlx_win, (t_xy){x * CELL_SIZE, y * CELL_SIZE}, (t_xy){CELL_SIZE, CELL_SIZE}, COLOR_RED);
		}
	}
}

char** init_2d_array(int rows, int cols) 
{
	char** array = (char**)malloc(rows * (sizeof(char*) + 1));
	if (array == NULL) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	int sec = -1;
	while(++sec < rows)
	{
		array[sec] = (char*)malloc(cols * (sizeof(char) + 1));
		if (array[sec] == NULL) {
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		int j = -1;
		while(++j < rows)
			array[sec][j] = "01"[randomOneOrZero()];
		array[sec][j] = '\0';
	}
	array[sec] = NULL;
	return array;
}

t_xy angleToVector(double angle)
{
	return (t_xy){(cos(angle)), (sin(angle))};
}

double deg2rad(double num)
{
	return((M_PI / 180) * num);
}


t_data *new_img(void *mlx, int width, int height)
{
	t_data	*img = malloc(sizeof(t_data));
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	return(img);
}

void draw_line(void *mlx, void *mlx_win, t_xy start, t_xy end, int color) {
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xIncrement = (float)dx / (float)steps;
	float yIncrement = (float)dy / (float)steps;
	float x = (float)start.x;
	float y = (float)start.y;

	for (int sec = 0; sec <= steps; sec++) {
		mlx_pixel_put(mlx, mlx_win, (int)x, (int)y, color);
		x += xIncrement;
		y += yIncrement;
	}
}

t_xy op(t_xy xy1, t_xy xy2, char op)
{
	if(op == '*')
		return (t_xy){xy1.x * xy2.x, xy1.y * xy2.y};
	if(op == '+')
		return (t_xy){xy1.x + xy2.x, xy1.y + xy2.y};
	if(op == 'i')
		return (t_xy){(int)xy1.x, (int)xy1.y};
	return (t_xy){0,0};
}

t_xy draw_line_dir(void *mlx, void * mlx_win, t_xy start, double direction, double distance, int color)
{
	double x;
	double y;
	double step = 0.1; // Adjust the step size as needed for smoothness
	for (double t = 0; t <= distance; t += step) 
	{
		mlx_pixel_put(mlx, mlx_win, start.x + t * cos(direction), start.y + t * sin(direction), color);
	}
	return((t_xy){start.x + distance * cos(direction), start.y + distance * sin(direction)});
}