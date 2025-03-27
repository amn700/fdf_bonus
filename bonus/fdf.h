#ifndef FDF_BONUS_H
#define FDF_BONUS_H

#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h" 

#include "MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_dims{
	uint32_t	x;
	uint32_t	y;
}	t_dims;

typedef struct s_Color_duo{
	uint32_t	color1;
	uint32_t	color2;
}	t_Color_duo;

typedef struct s_screen {
    double x;
    double y;
} t_screen;

typedef struct s_isom{
	double cos;
	double sin;
}	t_isom;

typedef struct s_offset{
	int x;
	int y;
}	t_offset;

typedef struct s_point {
    int z;
    int color;
	t_screen final;
} t_point;

typedef struct s_line{
	t_point		*line;
	uint32_t	max_x;
}	t_line;


typedef struct s_rotation {
    double x;
    double y;
    double z;
} t_rotation;

typedef struct s_zscale{
	int min;
	int max;
}	t_zscale;

typedef struct s_fdf{
	mlx_texture_t	*front_page;
	mlx_image_t		*img;
	t_rotation		rotation;
	t_line			*map;
	mlx_t			*mlx_ptr;
	uint32_t		width;
	uint32_t		height;
	int 			angle;
	int 			offset_x;
	int 			offset_y;
	int 			scale_factor;
	int 			diagnol_lines;
	int 			flag;
}	t_fdf;

// write the prototype of every function in these files (controls.c fdf_shit.c parse_map.c math.c line.c)
void control(t_fdf *data, mlx_key_data_t keydata);
void scale(t_fdf *data, mlx_key_data_t keydata);
void rotations(t_fdf *data, mlx_key_data_t keydata);
void key_handler(mlx_key_data_t keydata, void *param);
int interpolate_color(int color1, int color2, float t);
void draw_line(t_screen one, t_screen two, mlx_image_t *img, t_Color_duo c);
void draw_horizontal_line(t_fdf data);
void draw_vertical_line(t_fdf data);
void draw_diagnol_lines(t_fdf data);
double to_radians(int degrees);
void rotate_x(double *y, double *z, double theta);
void rotate_y(double *x, double *z, double theta);
void rotate_z(double *x, double *y, double theta);
void render_map(t_fdf *data);

uint32_t get_largest_width(t_fdf *data);
void calculate_offsets(t_fdf *data, mlx_image_t *img);
int	set_scalefactor(t_fdf *data, mlx_image_t *img);
void	free_matrix_fdf(int **matrix);
int	check_extention(char * file_name);
int	set_max_x_values(char *file_name, t_line *array);

int allocate_points(t_fdf *data);
int	populate_every_point(t_fdf data, t_line *array, char *file_name);
int	ft_atoi_fdf(const char *nptr, int *i);
int	locate(const char *s, int c);
int max(int a, int b);
u_int32_t	hexer(char *str, char *upper_base ,char *lower_base);
u_int32_t	get_color(char *point, int i);
int	count_words(char *str);
int	check_map(int width, char *line);
int	get_width_and_height(char* file_name, t_fdf* data);
void	init_struct_fdf(t_fdf* data);
#endif