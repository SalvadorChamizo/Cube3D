/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:25:53 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/20 16:03:30 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdbool.h>

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
