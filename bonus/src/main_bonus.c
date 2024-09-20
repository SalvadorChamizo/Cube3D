/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:25:53 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/20 13:16:06 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdbool.h>

/*int	init_data_variables(t_data *data)
{
	data->file = NULL;
	data->mlx = NULL;
	data->background = NULL;
	data->walls = NULL;
	data->bonus = NULL;
	data->ray_number = 0;
	data->move = 0;
	data->prev_mouse_x = 0;
	data->prev_map_x = 0;
	data->prev_map_y = 0;
	data->open_flag = 0;
	data->animation_loop = 0;
	data->textures.no_flag = 0;
	data->textures.so_flag = 0;
	data->textures.we_flag = 0;
	data->textures.ea_flag = 0;
	data->textures.c_flag = 0;
	data->textures.f_flag = 0;
	data->map.map = NULL;
	data->map.map_line = 0;
	data->prev_mouse_x = -1;
	return (0);
}*/

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
	ft_load_textures(&data);
	ft_game(&data);
	ft_free_split(data.map.map);
	free_textures_memory(&data);
	ft_delete_textures(&data);
	return (0);
}
