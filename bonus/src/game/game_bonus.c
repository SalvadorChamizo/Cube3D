/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/16 11:04:02 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

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

void	ft_game(t_data *data)
{
	game_init(data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
}
