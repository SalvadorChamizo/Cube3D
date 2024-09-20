/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:57:20 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/20 16:03:53 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_texture_flags(t_data *data)
{
	data->textures.no_flag = 0;
	data->textures.so_flag = 0;
	data->textures.we_flag = 0;
	data->textures.ea_flag = 0;
	data->textures.c_flag = 0;
	data->textures.f_flag = 0;
}

void	init_player_variables(t_data *data)
{
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.map_x = 0;
	data->player.map_y = 0;
	data->player.angle = 0;
}

void	init_texture_variables(t_data *data)
{
	init_texture_flags(data);
	data->textures.no_texture = NULL;
	data->textures.so_texture = NULL;
	data->textures.we_texture = NULL;
	data->textures.ea_texture = NULL;
	data->textures.no_path = NULL;
	data->textures.so_path = NULL;
	data->textures.we_path = NULL;
	data->textures.ea_path = NULL;
	data->textures.c_color = 0;
	data->textures.f_color = 0;
}

int	init_data_variables(t_data *data)
{
	init_texture_variables(data);
	init_player_variables(data);
	data->file = NULL;
	data->mlx = NULL;
	data->background = NULL;
	data->walls = NULL;
	data->ray_number = 0;
	data->move = 0;
	data->map.map = NULL;
	data->map.map_line = 0;
	data->map.map_size_x = 0;
	data->map.map_size_y = 0;
	return (0);
}
