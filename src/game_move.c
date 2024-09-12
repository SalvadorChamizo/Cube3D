/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:00:56 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/12 17:44:20 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angle_move(t_data *data, double angle)
{
	double			move_x;
	double			move_y;

	move_x = (cos(angle * M_PI / 180) * data->move);
	move_y = (sin(angle * M_PI / 180) * data->move);
	if (check_cell_move(data->mini.minipoint, data, 0, move_y))
	{
		data->player.pos_y += move_y / 64;
	}
	if (check_cell_move(data->mini.minipoint, data, move_x, 0))
	{
		data->player.pos_x += move_x / 64;
	}
}

void	angle_act(double *angle, double var)
{
	*angle += var;
	if (*angle > 359)
		*angle = 0;
	if (*angle < 0)
		*angle = 359;
}
