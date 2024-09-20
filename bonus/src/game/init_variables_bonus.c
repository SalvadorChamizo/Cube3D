/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:01:04 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/20 15:02:06 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

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
	data->textures.do_texture = NULL;
	data->textures.no_path = NULL;
	data->textures.so_path = NULL;
	data->textures.we_path = NULL;
	data->textures.ea_path = NULL;
	data->textures.do_path = NULL;
	data->textures.c_color = 0;
	data->textures.f_color = 0;
}

void	init_animation_variables(t_data *data)
{
	data->animation.animation_1 = NULL;
	data->animation.animation_2 = NULL;
	data->animation.animation_3 = NULL;
	data->animation.animation_4 = NULL;
	data->animation.animation_5 = NULL;
	data->animation.flag = 0;
	data->animation.scale_x = 0;
	data->animation.scale_y = 0;
	data->animation.target_x = 0;
	data->animation.target_y = 0;
}

int	init_data_variables(t_data *data)
{
	init_texture_variables(data);
	init_player_variables(data);
	init_animation_variables(data);
	data->file = NULL;
	data->mlx = NULL;
	data->background = NULL;
	data->walls = NULL;
	data->bonus = NULL;
	data->ray_number = 0;
	data->move = 0;
	data->prev_map_x = 0;
	data->prev_map_y = 0;
	data->animation_loop = 0;
	data->map.map = NULL;
	data->map.map_line = 0;
	data->map.map_size_x = 0;
	data->map.map_size_y = 0;
	data->prev_mouse_x = -1;
	return (0);
}
