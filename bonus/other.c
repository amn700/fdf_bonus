// u_int32_t	get_color(char *point, int i)
// {
//     u_int32_t full_rgba;
// 	char *upper_base = "0123456789ABCDEF";
// 	char *lower_base = "0123456789abcdef";

//     if (ft_strncmp(&point[i], ",0x", 3))
//         return (0xFFFFFFFF);

//     i += 3;
// 	full_rgba = hexer(&point[i], upper_base, lower_base);
// 	return (full_rgba << 8) | 0xFF;
// }


// u_int32_t	get_color(char *point, int i)
// {
//     int place = 0;
//     int color;
//     u_int32_t full_rgba = 0;

//     if (ft_strncmp(&point[i], ",0x", 3))
//         return (0xFFFFFFFF);

//     i += 3;
//     while (place < 3)
//     {
//         if (!single_color(point, &i, &color))
//             break;
// 		full_rgba |= (color << (16 - (place * 8)));
//         place++;
//     }
// 	full_rgba |= 0xFF;
//     return (full_rgba);
// }
    // if (color <= 0xFF) {         // Single-byte format (grayscale)
    //     r = g = b = color;
    // } else if (color <= 0xFFFF) { // Short format (0xRRGG)
    //     r = (color >> 8) & 0xFF;
    //     g = color & 0xFF;
    //     b = 0; // No blue value, default to 0
    // } else {                      // Full format (0xRRGGBB)
    //     r = (color >> 16) & 0xFF;
    //     g = (color >> 8) & 0xFF;
    //     b = color & 0xFF;
    // }

    // return (r << 24) | (g << 16) | (b << 8) | 255; // RGBA (A = 255)
	
// int single_color(char *point, int *i, int *color)
// {
//     char *base_h = "0123456789ABCDEF";
//     char *base_l = "0123456789abcdef";
//     int value;

//     *color = 0;
//     while (point[*i] && (locate(base_h, point[*i]) != -1 || locate(base_l, point[*i]) != -1))
//     {
// 		if(locate(base_h, point[*i]) == -1)
// 			value = locate(base_l, point[*i]);
// 		else
//         	value = locate(base_h, point[*i]);
//         *color = (*color << 4) | value;
//         (*i)++;
//     }
//     return (1);
// }
// int	allocate_points(t_fdf *data)
// {
// 	uint32_t y = 0;
// 	while (y < data->height)
// 	{
// 		data->map[y].line = calloc(sizeof(t_point) , data->map[y].max_x);
// 		if (!data->map[y].line)
// 			return (abort_free(data, y), 0);
// 		y++;
// 	}
// 	return (1);
// }

// static void core_populate(t_line *array, char *line, int y)
// {
// 	char	**matrix;
// 	uint32_t		x;
// 	int		i;

// 	x = 0;
// 	i = 0;
// 	matrix = ft_split(line, 32);
// 	if (!matrix)
// 		return ;
// 	while (x < array[y].max_x)
// 	{
// 		i = 0;
// 		array[y].line[x].z = ft_atoi_fdf(matrix[x], &i);
// 		array[y].line[x].color = get_color(matrix[x], i);
// 		// printf("color: %d\n", array[y].line[x].color);
// 		x++;
// 	}
// 	free(matrix);
// }

// int single_color(char *point, int *i, int *color)
// {
// 	char *base = "0123456789ABCDEF";
// 	*color = 0;

// 	if (locate(base, point[(*i)]) == -1 || locate(base, point[(*i)+ 1]) == -1)
// 		return (0);
// 	*(color) = locate(base, point[(*i)] * 16 + locate(base, point[(*i)+1]));
// 	*(i) += 2;
// 	return (1);
// }

// int get_rgba(int r, int g, int b, int a)
// {
//     return (r << 24) | (g << 16) | (b << 8) | a;
// }

// uint32_t get_color(char *point, int i)
// {
//     int place = 0;
//     int color;
//     int full_rgb = 0;

//     if (ft_strncmp(&point[i], ",0x", 3))
//         return 0xFFFFFFFF;

//     i += 3;
//     while (place < 6)
//     {
//         if (!single_color(point, &i, &color))
//             return 0xFFFFFFFF;
//         full_rgb = (full_rgb << 4) | color;
//         place++;
//     }
//     return (full_rgb << 8) | 0xFF;
// }


// t_point	*points_array(char *file_name, fdf *data, int points_count)
// {
// 	t_point *points = malloc(sizeof(t_point) * points_count);
// 	if (!points)
// 		return 0;
// 	int fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		return 0;
// 	char *line = get_next_line(fd);
// 	if (!line)
// 		return (close(fd), 0);
// 	int i = 0;
// 	int j = 0;
// 	while (line)
// 	{
// 		char **split = ft_split(line, 32);
// 		if (!split)
// 			return (close(fd), 0);
// 		while (split[j])
// 		{
// 			points[i].x = j;
// 			points[i].y = i;
// 			points[i].z = ft_atoi(split[j]);
// 			if (ft_strchr(split[j], ','))
// 				points[i].color = ft_strdup(ft_strchr(split[j], ',') + 1);
// 			else
// 				points[i].color = NULL;
// 			j++;
// 			i++;
// 		}
// 		free(split);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return points;
// }

// t_point	*get_points(char *file_name, fdf *data)
// {
// 	t_point *points;
// 	int fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		return 0;
// 	char	*line = get_next_line(fd);
// 	int points_count = 0;
// 	if (!line)
// 		return (close(fd), 0);
// 	while (line)
// 	{
// 		points_count += count_words(line, 32);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (points_array(file_name, data, points_count));
// }

// int		parse_map(t_fdf *data, char *file_name)
// {
// 	init_struct_fdf(data);
// 	if (!get_height(file_name, data))
// 		return (free(data), 0);
// 	if (!get_width(file_name, data))
// 		return (free(data), 0);
// //	extract from the file the coordinates of the points and the color of each point
// 	t_point *points = get_points(file_name, data);

// 	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf", false);
// 	if (!data->mlx_ptr)
// 		return (free(data), 0);
// 	return 1;
// }

// int		allocate_int_matrix(fdf* data, char *filename)
// {
// 	int		i = 0;
// 	char	*line = 0;
// 	int 	len = 0;
// 	int		fd = open (filename, O_RDONLY);
// 	if (fd < 0) 
// 		return 0;
// 	data->z_matrix = malloc(sizeof(int *) * (data->height));
// 	if (!data->z_matrix)
// 		return 0;
// 	line = get_next_line(fd);
// 	if (!line)
// 		return (close(fd), 0);
// 	while (!line)
// 	{
// 		data->z_matrix[i] = malloc(sizeof(int) * count_words(line, 32));
// 		if (!data->z_matrix[i])
// 			return 0;
// 		i++;
// 	}
// 	return 1;
// }

// void	populate_line(fdf *data, char** matrix, int i)
// {
// 	int j = 0;
// 	while (j < data->width)
// 	{
// 		data->z_matrix[i][j] = ft_atoi(matrix[j]);
// 		if (matrix[j][0] == '\n')
// 			break;
// 		j++;
// 	}
// }

// int		populate_matrix(char* file_name, fdf * data)
// {
// 	int i = 0;
// 	char **matrix;
// 	char * line = NULL;
// 	int fd = open (file_name, O_RDONLY);
// 	if(fd < 0)
// 		return 0;
// 	while (i < data->height)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			return(close(fd), 0);
// 		matrix = ft_split(line, 32);
// 		if (!matrix)
// 			return(free(line), close(fd), 0);
// 		free(line);
// 		populate_line(data, matrix, i);
// 		free(matrix);
// 		i++;
// 	}
// 	close(fd);
// 	return 1;
// }

			// screen.x = (int)(dims.x - dims.y) * cos(to_radians(data->angle));
			// screen.y = (dims.x + dims.y) * sin(to_radians(data->angle)) - data->map[dims.y].line[dims.x].z;
            // screen.x = dims.x * cos(data->angle) - dims.y * sin(data->angle);
            // screen.y = dims.x * sin(data->angle) + dims.y * cos(data->angle);

            // screen.x = x * cos(theta) + z * sin(theta);
            // p->z = -x * sin(theta) + z * cos(theta);
            // apply_rotations(data, data->rotation.x, data->rotation.y, data->rotation.z);
// void draw_line(t_screen one, t_screen two, mlx_image_t *img)
// {
// 	t_screen 	d;
// 	t_screen 	screen;
// 	float 		step;
// 	float 		i;

// 	screen.x = one.x;
// 	screen.y = one.y;
// 	d.x = fabs(two.x - one.x);
// 	d.y = fabs(two.y - one.y);
// 	// step = ((d.x >= d.y) ? d.x : d.y);
// 	if (d.x >= d.y)
// 		step = d.x;
// 	else
// 		step = d.y;

// 	d.x = d.x / step;
// 	d.y = d.y / step;
// 	i = 1;
// 	// while (i < step)
// 	// {
// 	// 	if (screen.x >= (float)0 && screen.y >= (float)0 && screen.x < (float)img->width && screen.y < (float)img->height)
// 	// 		mlx_put_pixel(img, screen.x, screen.y, -1);
// 	// 	screen.x = screen.x + d.x;
// 	// 	screen.y = screen.y + d.y;
// 	// 	i++;
// 	// }
// 	while (i <= step) // Ensure last pixel is drawn
// 	{
// 		if (screen.x >= 0 && screen.y >= 0 && screen.x < img->width && screen.y < img->height)
// 			mlx_put_pixel(img, (int)screen.x, (int)screen.y, -1); // Cast to int

// 		screen.x += d.x;
// 		screen.y += d.y;
// 		i++;
// 	}

// }






            // // Draw lines to adjacent points
            // if (dims.x > 0)
			// {
            //     // Draw line to the left neighbor
            //     int left_x = data->map[dims.y].line[dims.x - 1].final->x;
            //     int left_y = data->map[dims.y].line[dims.x - 1].final->y;
            //     draw_line(img, final_x, final_y, left_x, left_y, data->map[dims.y].line[dims.x].color);
            // }
            // if (dims.y > 0 && dims.x < data->map[dims.y - 1].max_x)
			// {
            //     // Draw line to the top neighbor
            //     int top_x = data->map[dims.y - 1].line[dims.x].final->x;
            //     int top_y = data->map[dims.y - 1].line[dims.x].final->y;
            //     draw_line(img, final_x, final_y, top_x, top_y, data->map[dims.y].line[dims.x].color);
            // }

// void render_map(t_fdf *data, mlx_image_t *img)
// {
// 	t_dims		dims;
// 	t_dims		screen;
// 	t_offset	offset;
// 	t_isom		calcule;
// 	int			scale_factor;
// 	int			scale_z;

//     dims.y = 0;
// 	calcule = set_isom(30);
//     scale_factor = set_scalefactor(data, img);
// 	offset = set_offset(data, img, scale_factor);
//     while (dims.y < data->height)
// 	{
//         dims.x = 0;
//         while (dims.x < data->map[dims.y].max_x)
// 		{
// 			scale_z = data->map[dims.y].line[dims.x].z * scale_factor / 10;//min z , maz z gets u the devison
// 			screen.y = (dims.x + dims.y) * calcule.sin - scale_z;
// 			screen.y = ((dims.x + dims.y) * calcule.sin )- scale_z;
//             screen.x = (dims.x - dims.y) * calcule.cos;
//             final.x =  offset.x + ((screen.x) * scale_factor);
// 			final.y =  offset.y + ((screen.y) * scale_factor);
//             if (final.x >= 0 && final.x < img->width && final.y >= 0 && final.y < img->height)
//             	mlx_put_pixel(img, final.x, final.y, -1);
//             	// mlx_put_pixel(img, dims.x, dims.y, data->map[dims.y].line[dims.x].color);
//             	// mlx_put_pixel(img, screen.x, screen.y, data->map[dims.y].line[dims.x].color);
//             dims.x++;
//         }
//         dims.y++;
//     }
// }
// void render_map(t_fdf *data, mlx_image_t *img)
// {
// 	t_dims 		final;
// 	t_dims		dims;
// 	t_dims		screen;
// 	t_offset	offset;
// 	t_isom		calcule;
// 	int			scale_factor;
// 	int			scale_z;

//     dims.y = 0;
// 	calcule = set_isom(30);
//     scale_factor = set_scalefactor(data, img);
// 	offset = set_offset(data, img, scale_factor);
//     while (dims.y < data->height)
// 	{
//         dims.x = 0;
// 		// scale_z = data->map[dims.y].line[dims.x].z * scale_factor / 10;//min z , maz z gets u the devison
// 		// screen.y = (dims.x + dims.y) * calcule.sin - scale_z;
//         while (dims.x < data->map[dims.y].max_x)
// 		{
// 			screen.y = (dims.x + dims.y) * calcule.sin - data->map[dims.y].line[dims.x].z;
//             screen.x = (dims.x - dims.y) * calcule.cos;
//             final.x =  ((offset.x +screen.x) * scale_factor);
// 			final.y =  ((offset.y +screen.y) * scale_factor);
//             if (final.x >= 0 && final.x < img->width && final.y >= 0 && final.y < img->height)
//             	mlx_put_pixel(img, final.x, final.y, data->map[dims.y].line[dims.x].color);
//             dims.x++;
//         }
//         dims.y++;
//     }
// }
	// for(int y = 0; y < data.height; y++)
	// {
	// 	for(int x = 0; x < data.map[y].max_x; x++)
	// 	{
	// 		ft_printf("%-10i",data.map[y].line[x].color);
	// 		ft_printf("%-10i",data.map[y].line[x].z);
	// 	}
	// 	ft_printf("\n");
	// }


	// Set every pixel to white
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	// // Display an instance of the image
	// if (mlx_image_to_window(data->mlx_ptr, img, 0, 0) < 0)
	// 	return 1;
	
	// int i = 0;
	// while (i < HEIGHT)
	// 	mlx_put_pixel(img, i++, 10, 0x11000000);
	// mlx_put_pixel(img, 20, 20, 0x00110000);
	// mlx_put_pixel(img, 30, 30, 0x00001100);
	// mlx_put_pixel(img, 40, 40, 0x00000011);

	// mlx_loop(data->mlx_ptr);
	// mlx_close_window(data->mlx_ptr);
	// mlx_terminate(data->mlx_ptr);
	// return (EXIT_SUCCESS);
// 	void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx - dy;

//     while (1) {
//         // Draw the pixel if it's within the image boundaries
//         if (x0 >= 0 && x0 < img->width && y0 >= 0 && y0 < img->height) {
//             mlx_put_pixel(img, x0, y0, color);
//         }

//         // Break if we've reached the end point
//         if (x0 == x1 && y0 == y1) break;

//         int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }

// // Render the map with isometric projection
// void render_map(t_fdf *data, mlx_image_t *img) {
//     t_dims dims;
//     t_dims screen;
//     t_offset offset;
//     t_isom calcule;
//     int scale_factor;

//     // Initialize isometric transformation values
//     calcule = set_isom(30);

//     // Calculate scale factor and offset
//     scale_factor = set_scalefactor(data, img);
//     offset = set_offset(data, img, scale_factor);

//     // Render the map
//     for (dims.y = 0; dims.y < data->height; dims.y++) {
//         for (dims.x = 0; dims.x < data->map[dims.y].max_x; dims.x++) {
//             // Apply isometric transformation
//             screen.x = (dims.x - dims.y) * calcule.cos;
//             screen.y = (dims.x + dims.y) * calcule.sin - data->map[dims.y].line[dims.x].z;

//             // Scale and offset the coordinates
//             int final_x = offset.x + (screen.x * scale_factor);
//             int final_y = offset.y + (screen.y * scale_factor);

//             // Store the final coordinates for later use
//             // data->map[dims.y].line[dims.x].final_x = final_x;
//             // data->map[dims.y].line[dims.x].final_y = final_y;

//             // Draw the point
//             if (final_x >= 0 && final_x < img->width && final_y >= 0 && final_y < img->height) {
//                 mlx_put_pixel(img, final_x, final_y, data->map[dims.y].line[dims.x].color);
//             }

//             // Draw lines to adjacent points
//             if (dims.x > 0) {
//                 // Draw line to the left neighbor
//                 int left_x = final_x;
//                 int left_y = final_y;
//                 draw_line(img, final_x, final_y, left_x, left_y, data->map[dims.y].line[dims.x].color);
//             }
//             if (dims.y > 0 && dims.x < data->map[dims.y - 1].max_x) {
//                 // Draw line to the top neighbor
//                 int top_x = final_x;
//                 int top_y = final_y;
//                 draw_line(img, final_x, final_y, top_x, top_y, data->map[dims.y].line[dims.x].color);
//             }
//         }
//     }
// }

