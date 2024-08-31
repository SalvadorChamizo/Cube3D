/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/08/31 18:44:22 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_size(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(map->map[i])
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
	mini->floor_texture = mlx_load_png("./minifloor.png");
	mini->minipoint_texture = mlx_load_png("./miniplayer.png");
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
			else
				mlx_image_to_window(data->mlx, data->mini.floor, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

void ft_hook(void* param)
{
	t_data		*data = param;
	mlx_image_t	*image = data->mini.minipoint;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		image->instances[0].y -= 4;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		image->instances[0].y += 4;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 4;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 4;
}

void	ft_game(t_data *data)
{
	map_size(&data->map);
	data->mlx = mlx_init(data->map.map_size_x * 64, data->map.map_size_y * 64, "so_long", true);
	mini_imagen_init(&data->mini, data);
	print_mini_map(data);
	if (mlx_image_to_window(data->mlx, data->mini.minipoint, (1 * 64) + 32/2, (1 * 64) + 32/2) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		//return(EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
}