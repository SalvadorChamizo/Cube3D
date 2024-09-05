/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:38:50 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/05 16:54:17 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    check_borders(mlx_image_t *image, t_data *data, double move_x, double move_y)
{
    int check_x;
	int check_x2;
    int check_y;
	int check_y2;
	(void)image;

	if (isnan(move_x))
	{
		check_x = (int)floor((data->player.pos_x + 0.25));
		check_x2 = (int)floor((data->player.pos_x - 0.25));
	}
	else
	{
		check_x = (int)floor((data->player.pos_x + 0.25) + (move_x / 64));
		check_x2 = (int)floor((data->player.pos_x - 0.25) + (move_x / 64));
	}
	if (isnan(move_y))
	{
		check_y = (int)floor((data->player.pos_y + 0.25));
		check_y2 = (int)floor((data->player.pos_y - 0.25));
	}
	else
	{
		check_y = (int)floor((data->player.pos_y + 0.25) + (move_y / 64));
		check_y2 = (int)floor((data->player.pos_y - 0.25) + (move_y / 64));
	}
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

bool	check_cell_move(mlx_image_t *image, t_data *data, double move_x, double move_y)
{
	int new_x;
	int new_y;

	new_x = (image->instances[0].x + move_x) / 64;
	new_y = (image->instances[0].y + move_y) / 64;
    if (!check_borders(image, data, move_x, move_y))
	{
		return (false);
	}
	data->player.map_x = data->player.pos_x + move_x / 64;
	data->player.map_y = data->player.pos_y + move_y / 64; 
	return (true);
}