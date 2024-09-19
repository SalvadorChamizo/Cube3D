/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:02:54 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/19 17:06:17 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

uint32_t get_plane_pixel_color(double x, double y, mlx_texture_t *texture)
{
	uint32_t index;
	uint8_t rgba[4];
	unsigned int i;

	i = 0;
	if (!texture || !texture->pixels || x >= texture->width || y >= texture->height)
		return 0;

	index = ((uint32_t)y * texture->width + (uint32_t)x) * texture->bytes_per_pixel;
	while (i < 4)
	{
		rgba[i] = texture->pixels[index + i];
		i++;
	}
	return (pack_rgba(rgba));
}

void	draw_animation(t_data *data, mlx_texture_t *texture)
{
	uint32_t	color;
	int			i;
	int			j;

	i = 0;
	data->animation.scale_x = (double)texture->width / (ANIMATION_WIDTH);
	data->animation.scale_y = (double)texture->height / (ANIMATION_HEIGHT);
	data->animation.target_x = (WIDTH - ANIMATION_WIDTH - 100);
	data->animation.target_y = HEIGHT - ANIMATION_HEIGHT + 15;
	while (i < ANIMATION_WIDTH)
	{
		j = 0;
		while (j < ANIMATION_HEIGHT)
		{
			color = get_plane_pixel_color(i * data->animation.scale_x, \
				j * data->animation.scale_y, texture);
			if (color != 0)
				mlx_put_pixel(data->walls, data->animation.target_x + i, \
					data->animation.target_y + j, color);
			j++;
		}
		i++;
	}
}

void	charge_animation_textures(t_data *data)
{
	data->animation.flag = 1;
	data->animation.animation_1 = mlx_load_png("./textures/tile000.png");
	data->animation.animation_2 = mlx_load_png("./textures/tile001.png");
	data->animation.animation_3 = mlx_load_png("./textures/tile002.png");
	data->animation.animation_4 = mlx_load_png("./textures/tile003.png");
	data->animation.animation_5 = mlx_load_png("./textures/tile004.png");
	if (!data->animation.animation_1 || !data->animation.animation_2 || !data->animation.animation_3
		|| !data->animation.animation_4 || !data->animation.animation_5)
	{
		print_error("Failed to open animation texture.\n");
		data->animation.flag = -1;
	}
}

void	loop_animation_texture(t_data *data)
{
	if (data->animation.flag == -1)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (data->animation_loop == 0)
			draw_animation(data, data->animation.animation_1);
		if (data->animation_loop == 1)
			draw_animation(data, data->animation.animation_2);
		if (data->animation_loop == 2)
			draw_animation(data, data->animation.animation_3);
		if (data->animation_loop == 3)
			draw_animation(data, data->animation.animation_4);
		if (data->animation_loop == 4)
			draw_animation(data, data->animation.animation_5);
		data->animation_loop++;
		if (data->animation_loop == 6)
			data->animation_loop = 0;
	}
	else
		data->animation_loop = 0;
	if (data->animation_loop == 0)
		draw_animation(data, data->animation.animation_1);
}
