/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 04:40:39 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 04:56:47 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_fdf_map(t_fdf *data)
{
	uint32_t y = 0;
	while (y < data->height)
	{
		free(data->map[y].line);
		y++;
	}
	free(data->map);
}

int	main(int argc, char** argv)
{
	if (argc != 2)
		return (write(2, "error0\n\n", 7), 1);
	t_fdf data;
	init_struct_fdf(&data);
	if(!check_extention(argv[1]))
		return (1);
	if (!get_width_and_height(argv[1], &data))
		return (write(2, "error1\n", 7), 1);
	data.map = malloc (sizeof(t_line) * data.height);
	if (!data.map)
		return (1);
	if (!set_max_x_values(argv[1], data.map))
		return (write(2, "error2\n", 7),free(data.map), 1);
	if (!allocate_points(&data))
		return (write(2, "error3\n", 7),free(data.map), 1);
	if (!populate_every_point(data, data.map, argv[1]))
		return (write(2, "error4\n", 7),free_fdf_map(&data), 1);
	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf_bonus", false);
	if (!data.mlx_ptr)
		return (write(2, "error5\n", 7),free_fdf_map(&data), 1);
	data.front_page= mlx_load_png("front.png");
	if (!data.front_page)
		return 1;
	data.img = mlx_texture_to_image(data.mlx_ptr, data.front_page);
	if (!data.img)
		return 1;
	if (mlx_image_to_window(data.mlx_ptr, data.img, 0, 0) < 0)
		return 1;
	data.scale_factor = set_scalefactor(&data, data.img);
	calculate_offsets(&data, data.img);
	mlx_key_hook(data.mlx_ptr, key_handler, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
