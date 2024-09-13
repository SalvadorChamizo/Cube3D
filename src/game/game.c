/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/13 15:12:17 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_size(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		if ((int)ft_strlen(map->map[i]) > j)
			j = ft_strlen(map->map[i]);
		i++;
	}
	map->map_size_x = j;
	map->map_size_y = i;
}

void	imagen_init(t_data *data, mlx_image_t **imagen)
{
	*imagen = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!*imagen)
	{
		print_error("Failed creating floor-ceiling image\n");
		exit(FAILURE);
	}
	if (mlx_image_to_window(data->mlx, *imagen, 0, 0) == -1)
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
	if (data->player.ray[0].DeltaDistY)
		mlx_delete_image(data->mlx, data->board);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		angle_move(data, data->player.angle);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		angle_move(data, data->player.angle + 180);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		angle_move(data, data->player.angle - 90);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		angle_move(data, data->player.angle + 90);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		angle_act(&data->player.angle, -3);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		angle_act(&data->player.angle, 3);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->move = 12;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->move = 4;
	imagen_init(data, &data->board);
	print_ray(data, &data->player);
}

void	game_init(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!data->mlx)
	{
		print_error("Failed to initialiaze mlx.\n");
		exit(1);
	}
	imagen_init(data, &data->screen);
	imagen_init(data, &data->board);
	data->move = 4;
	find_player_position(data, data->map.map);
	paint_floor_ceiling(data);
}

void	ft_game(t_data *data)
{
	map_size(&data->map);
	game_init(data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
}
