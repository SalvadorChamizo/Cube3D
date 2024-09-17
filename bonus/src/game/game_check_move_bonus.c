/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check_move_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:38:50 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/17 16:12:45 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

bool	check_move_is_valid(t_data *data, double move_x, double move_y)
{
	int	check_x;
	int	check_x2;
	int	check_y;
	int	check_y2;

	check_x = (int)floor((data->player.pos_x + 0.25) + (move_x / 64));
	check_x2 = (int)floor((data->player.pos_x - 0.25) + (move_x / 64));
	check_y = (int)floor((data->player.pos_y + 0.25) + (move_y / 64));
	check_y2 = (int)floor((data->player.pos_y - 0.25) + (move_y / 64));
	if (data->map.map[check_y][check_x] == '1'
		|| data->map.map[check_y][check_x] == 'D')
		return (false);
	if (data->map.map[check_y2][check_x] == '1'
		|| data->map.map[check_y2][check_x] == 'D')
		return (false);
	if (data->map.map[check_y][check_x2] == '1'
		|| data->map.map[check_y][check_x2] == 'D')
		return (false);
	if (data->map.map[check_y2][check_x2] == '1'
		|| data->map.map[check_y2][check_x2] == 'D')
		return (false);
	return (true);
}

bool	update_move(t_data *data, double move_x, double move_y)
{
	if (!check_move_is_valid(data, move_x, move_y))
		return (false);
	data->player.map_x = data->player.pos_x + move_x / 64;
	data->player.map_y = data->player.pos_y + move_y / 64;
	return (true);
}
