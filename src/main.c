/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:25:53 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/06 14:50:45 by schamizo         ###   ########.fr       */
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
	//find_player_position(&data, data.map.map);
	//paint_floor_ceiling(&data);
	//painting_everything(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free_split(data.map.map);
	free_textures_memory(&data);
}

/********************************************************************************* */

/*static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 10;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 10;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 10;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 10;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "cube3d", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}*/
