/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 04:41:21 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 06:33:19 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	handle_mlx(t_fdf *data)
{
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf", false);
	if (!data->mlx_ptr)
		return (0);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	if (argc != 2)
		return (write(2, "error1\n", 7), 1);
	if (!check_extention(argv[1]))
		return (1);
	init_struct_fdf(&data);
	if (!get_width_and_height(argv[1], &data))
		return (write(2, "error2\n", 7), 1);
	data.map = malloc(sizeof(t_line) * data.height);
	if (!data.map)
		return (1);
	if (!set_max_x_values(argv[1], data.map))
		return (write(2, "error3\n", 7), free(data.map), 1);
	if (!allocate_points(&data))
		return (write(2, "error4\n", 7), free(data.map), 1);
	if (!handle_mlx(&data))
		return (write(2, "error5\n", 7), free(data.map), 1);
	data.scale_factor = set_scalefactor(&data, data.img);
	calculate_offsets(&data, data.img);
	mlx_image_to_window(data.mlx_ptr, data.img, 0, 0);
	ft_draw(&data);
	mlx_loop(data.mlx_ptr);
}
