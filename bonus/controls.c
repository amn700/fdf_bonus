/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:13:47 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 04:40:49 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void control(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_UP) 
		data->offset_y -= 50;
	if (keydata.key == MLX_KEY_DOWN)
		data->offset_y += 50;
	if (keydata.key == MLX_KEY_LEFT)
		data->offset_x -= 50;
	if (keydata.key == MLX_KEY_RIGHT)
		data->offset_x += 50;
}

void scale(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_I)
		data->scale_factor += 2;
	if (keydata.key == MLX_KEY_O && data->scale_factor > 2)
		data->scale_factor -= 2;
}

void rotations(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_1)
		data->rotation.z += 5;
	if (keydata.key == MLX_KEY_2)
		data->rotation.z -= 5;
	if (keydata.key == MLX_KEY_4)
		data->rotation.y += 5;
	if (keydata.key == MLX_KEY_5)
		data->rotation.y -= 5;
	if (keydata.key == MLX_KEY_7)
		data->rotation.x += 5;
	if (keydata.key == MLX_KEY_8)
		data->rotation.x -= 5;
}

void key_handler(mlx_key_data_t keydata, void *param)
{
	t_fdf *data = (t_fdf*)param;
    if (keydata.action == MLX_PRESS)
    {
		if(keydata.key == MLX_KEY_ESCAPE)
			exit(0);
		if (keydata.key == MLX_KEY_T)
			data->diagnol_lines = !data->diagnol_lines;
		control(data, keydata);
		scale(data, keydata);
		rotations(data, keydata);
    }
	mlx_delete_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return;
	mlx_image_to_window(data->mlx_ptr, data->img, 0, 0);
	render_map(data);
	draw_horizontal_line(*data);
	draw_vertical_line(*data);
	if (data->diagnol_lines)
		draw_diagnol_lines(*data);
}
