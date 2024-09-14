/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:00:56 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/14 18:37:58 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_player_movement(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player_by_angle(data, data->player.angle);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_by_angle(data, data->player.angle + 180);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_by_angle(data, data->player.angle - 90);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_by_angle(data, data->player.angle + 90);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->move = 12;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->move = 4;
}

void	handle_player_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		adjust_angle(&data->player.angle, -3);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		adjust_angle(&data->player.angle, 3);
}

void	move_player_by_angle(t_data *data, double angle)
{
	double			move_x;
	double			move_y;

	move_x = (cos(angle * M_PI / 180) * data->move);
	move_y = (sin(angle * M_PI / 180) * data->move);
	if (update_move(data, 0, move_y))
	{
		data->player.pos_y += move_y / 64;
	}
	if (update_move(data, move_x, 0))
	{
		data->player.pos_x += move_x / 64;
	}
}

void	adjust_angle(double *angle, double var)
{
	*angle += var;
	if (*angle > 359)
		*angle = 0;
	if (*angle < 0)
		*angle = 359;
}
