/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:38:50 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/13 13:15:41 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_borders(t_data *data, double move_x, double move_y)
{
	int	check_x;
	int	check_x2;
	int	check_y;
	int	check_y2;

	check_x = (int)floor((data->player.pos_x + 0.25) + (move_x / 64));
	check_x2 = (int)floor((data->player.pos_x - 0.25) + (move_x / 64));
	check_y = (int)floor((data->player.pos_y + 0.25) + (move_y / 64));
	check_y2 = (int)floor((data->player.pos_y - 0.25) + (move_y / 64));
	if (data->map.map[check_y][check_x] == '1')
		return (false);
	if (data->map.map[check_y2][check_x] == '1')
		return (false);
	if (data->map.map[check_y][check_x2] == '1')
		return (false);
	if (data->map.map[check_y2][check_x2] == '1')
		return (false);
	return (true);
}

bool	check_cell_move(t_data *data, double move_x, double move_y)
{
	if (!check_borders(data, move_x, move_y))
		return (false);
	data->player.map_x = data->player.pos_x + move_x / 64;
	data->player.map_y = data->player.pos_y + move_y / 64;
	return (true);
}
