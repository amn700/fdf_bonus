#include "fdf.h"

uint32_t get_largest_width(t_fdf *data)
{
	uint32_t max = 0;
	uint32_t y = 0;
	while (y < data->height)
	{
		if (data->map[y].max_x > max)
			max = data->map[y].max_x;
		y++;
	}
	return (max);
}

void calculate_offsets(t_fdf *data, mlx_image_t *img)
{
    data->offset_x = (int)(img->width - data->scale_factor) / 2;
    data->offset_y = (int)(img->height - data->scale_factor) / 2;
}

int	set_scalefactor(t_fdf *data, mlx_image_t *img)
{
    double scale_x;
    double scale_y;
    double largest_width;
    largest_width = (double)get_largest_width(data);

    scale_x = img->width / (largest_width + 2);
    scale_y = img->height / (data->height + 2);  

    if (scale_x > scale_y)
        return (int)scale_x;
    return (int)scale_y;
}

void	free_matrix_fdf(int **matrix)
{
	int i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int	check_extention(char * file_name)
{
	size_t len = ft_strlen(file_name) - 4;
	file_name += len;
	if (!ft_strncmp(file_name, ".fdf", 4))
		return (1);
	return (0);
}

int	set_max_x_values(char *file_name, t_line *array)
{
	int y = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		array[y++].max_x = count_words(line);
		free(line);
	}
	close(fd);
	return (1);
}

static void	abort_free(t_fdf *data, int y)
{
	while (y >= 0)
	{
		free(data->map[y].line);
		y--;
	}
}

int allocate_points(t_fdf *data)
{
    uint32_t y = 0;
    while (y < data->height)
    {
        if (data->map[y].max_x <= 0)
            return (abort_free(data, y), 0);
        data->map[y].line = calloc(sizeof(t_point), data->map[y].max_x);
        if (!data->map[y].line)
            return (abort_free(data, y), 0);
        y++;
    }
    return (1);
}

static void core_populate(t_line *array, char *line, int y)
{
	char		**matrix;
	uint32_t	x;
	int			i;

	x = 0;
	matrix = ft_split(line, 32);
	if (!matrix)
		return;
	while (x < array[y].max_x)
	{
		i = 0;
		array[y].line[x].z = ft_atoi_fdf(matrix[x], &i);
		array[y].line[x].color = get_color(matrix[x], i);
		x++;
	}
	free_matrix_fdf((int **)matrix);
}


int	populate_every_point(t_fdf data, t_line *array, char *file_name)
{
	char 	*line;
	uint32_t		y ;

	y = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (y < data.height)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		core_populate(array, line, y);
		free(line);
		y++;
	}
	return (1);
}

int	ft_atoi_fdf(const char *nptr, int *i)
{
	int		sign;
	int		total;

	sign = 1;
	total = 0;
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		total = total * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	return (total * sign);
}

int	locate(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int max(int a, int b)
{
	if (a >= b)
		return a;
	return b;
}
u_int32_t	hexer(char *str, char *upper_base ,char *lower_base)
{
	int	flag;
	u_int32_t	total;
	int i;

	i = 0;
	total = 0;

	flag = max(locate(lower_base, str[i]), locate(upper_base, str[i]));
	i++;
	while (flag != -1)
	{
		total = total * 16 + flag;
		flag = max(locate(lower_base, str[i]), locate(upper_base, str[i]));
		i++;
	}
	return (total);
}

u_int32_t	get_color(char *point, int i)
{
    u_int32_t full_rgba;
	char *upper_base = "0123456789ABCDEF";
	char *lower_base = "0123456789abcdef";

    if (ft_strncmp(&point[i], ",0x", 3))
        return (0xFFFFFFFF);

    i += 3;
    // Parse the color value (e.g., 3 parts for RGB)
	int len = ft_strlen(&point[i]);
	if (point[i + len -1] == '\n')
		len--;
    full_rgba = hexer(&point[i], upper_base, lower_base);
	if (len == 8)
		return (full_rgba);
	return (full_rgba << 8) | 0xFF;
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == 32 || (str[i]>= 9 && str[i]<= 13))
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != 32 && !(str[i]>= 9 && str[i]<= 13))
			i++;
	}
	return (count);
}

int	check_map(int width, char *line)
{
	int count = count_words(line);
	if (count < width)
		return (ft_printf("Found wrong line length. Exiting."), 0);
	return 1;
}

int	get_width_and_height(char* file_name, t_fdf* data)
{
	int count = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0) 
		return 0;
	char *line = get_next_line(fd);
	if (!line)
		return (close(fd), (0));
	count++;
	data->width = count_words(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!check_map(data->width, line))
			return (free(line), (0));
		count++;
		free(line);
	}
	data->height = count;
	close (fd);
	return (1);
}

void	init_struct_fdf(t_fdf* data)
{
	data->flag = 1;
	data->front_page = NULL;
	data->img = NULL;
	data->height = 0;
	data->width = 0;
	data->angle = 0;
	data->offset_x = 0;
	data->offset_y = 0;
	data->scale_factor = 0;
	data->diagnol_lines = 0;
	data->rotation.x= 35.264;
	data->rotation.y= -45;
	data->rotation.z= 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
}
