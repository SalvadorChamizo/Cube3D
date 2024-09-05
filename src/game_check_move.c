/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:38:50 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/04 18:22:56 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    check_borders(mlx_image_t *image, t_data *data, int move_x, int move_y)
{
    int check_x;
	int check_x2;
    int check_y;
	int check_y2;

	check_x = (image->instances[0].x + move_x) / 64;
	check_x2 = (image->instances[0].x + 32 + move_x) / 64;
	check_y = (image->instances[0].y + move_y) / 64;
	check_y2 = (image->instances[0].y + 32 + move_y) / 64;
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

bool	check_cell_move(mlx_image_t *image, t_data *data, int move_x, int move_y)
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