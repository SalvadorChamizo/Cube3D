/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/15 16:10:16 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_init(t_data *data, mlx_image_t **image)
{
	*image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!*image)
	{
		print_error("Failed creating floor-ceiling image\n");
		exit(FAILURE);
	}
	if (mlx_image_to_window(data->mlx, *image, 0, 0) == -1)
	{
		print_error("Failed in mlx_image_to_window() for \
			floor-ceiling image\n");
		exit(FAILURE);
	}
}

void	ft_hook(void *param)
{
	t_data		*data;

	data = param;
	if (data->player.ray[0].delta_dist_y)
		mlx_delete_image(data->mlx, data->walls);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	handle_player_movement(data);
	handle_player_rotation(data);
	image_init(data, &data->walls);
	print_ray(data, &data->player);
}

void	game_init(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	if (!data->mlx)
	{
		print_error("Failed to initialiaze mlx.\n");
		exit(1);
	}
	image_init(data, &data->background);
	image_init(data, &data->walls);
	data->move = 4;
	find_player_position(data, data->map.map);
	paint_floor_ceiling(data);
}

void	mouse_move(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	diff_mouse_x;

	data = (t_data *)param;
	(void)ypos;
	if (data->prev_mouse_x == -1)
		data->prev_mouse_x = xpos;
	diff_mouse_x = data->prev_mouse_x - xpos;
	data->prev_mouse_x = xpos;
	if (diff_mouse_x < 0)
	{
		data->player.angle = data->player.angle + 0.3;
		if (data->player.angle > 359)
			data->player.angle = 0;
	}
	else if (diff_mouse_x > 0)
	{
		data->player.angle = data->player.angle - 0.3;
		if (data->player.angle < 0)
			data->player.angle = 359;
	}
}

void	ft_game(t_data *data)
{
	game_init(data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_move, data);
	mlx_loop(data->mlx);
}
