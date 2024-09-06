/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/06 13:01:13 by saroca-f         ###   ########.fr       */
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

void	mini_imagen_init(t_minimap *mini, t_data *data)
{
	mini->wall_texture = mlx_load_png("./miniwall.png");
	mini->minipoint_texture = mlx_load_png("./miniplayer.png");
	mini->floor_texture = mlx_load_png("./minifloor.png");
	mini->wall = mlx_texture_to_image(data->mlx, mini->wall_texture);
	mini->floor = mlx_texture_to_image(data->mlx, mini->floor_texture);
	mini->minipoint = mlx_texture_to_image(data->mlx, mini->minipoint_texture);
}

void	print_mini_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_size_y)
	{
		j = 0;
		while (j < data->map.map_size_x)
		{
			if (data->map.map[i][j] == '1')
				mlx_image_to_window(data->mlx, data->mini.wall, j * 64, i * 64);
			else if (data->map.map[i][j] == '0' || \
				data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' || \
				data->map.map[i][j] == 'W' || data->map.map[i][j] == 'E')
				mlx_image_to_window(data->mlx, data->mini.floor, j * \
					64, i * 64);
			j++;
		}
		i++;
	}
}

void	ft_hook(void *param)
{
	t_data		*data;

	data = param;
	if (data->player.ray[0].DeltaDistX)
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
	print_ray(data, &data->player);
}

void	ft_game(t_data *data)
{
	map_size(&data->map);
	find_player_position(data, data->map.map);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cube3d", true);
	mini_imagen_init(&data->mini, data);
	print_mini_map(data);
	data->board = mlx_new_image(data->mlx, data->map.map_size_x * 64, \
		data->map.map_size_y * 64);
	mlx_image_to_window(data->mlx, data->board, 0, 0);
	mlx_image_to_window(data->mlx, data->mini.minipoint, (data->player.pos_x \
		* 64) - 16, (data->player.pos_y * 64) - 16);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
}