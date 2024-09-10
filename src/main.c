/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:25:53 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/09 12:56:47 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"
#include "../MLX42/include/MLX42/MLX42.h"

#include <stdbool.h>

int	init_data_variables(t_data *data)
{
	data->textures.no_flag = 0;
	data->textures.so_flag = 0;
	data->textures.we_flag = 0;
	data->textures.ea_flag = 0;
	data->textures.c_flag = 0;
	data->textures.f_flag = 0;
	data->map.map = NULL;
	data->map.map_line = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		h;

	if (argc != 2)
	{
		print_error("Incorrect number of arguments\n");
		return (1);
	}
	h = 0;
	init_data_variables(&data);
	if (parse_map(argv[1], &data))
	{
		if (data.map.map)
			ft_free_split(data.map.map);
		free_textures_memory(&data);
		return (1);
	}
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!data.mlx)
	{
		print_error("Failed to initialiaze mlx.\n");
		exit(1);
	}
	data.screen = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.screen)
	{
		print_error("Failed creating floor-ceiling image\n");
		exit(FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.screen, 0, 0) == -1)
	{
		print_error("Failed in mlx_image_to_window() for floor-ceiling image\n");
		exit(FAILURE);
	}
	find_player_position(&data, data.map.map);
	paint_floor_ceiling(&data);
	ft_game(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free_split(data.map.map);
	free_textures_memory(&data);
}
