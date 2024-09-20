/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:14 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/20 14:27:48 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	mouse_move(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	diff_mouse_x;

	data = (t_data *)param;
	(void)ypos;
	if (data->prev_mouse_x == -1)
		data->prev_mouse_x = xpos;
	diff_mouse_x = data->prev_mouse_x - xpos;
	data->prev_mouse_x = xpos;
	if (diff_mouse_x < 0)
	{
		data->player.angle = data->player.angle + 0.3;
		if (data->player.angle > 359)
			data->player.angle = 0;
	}
	else if (diff_mouse_x > 0)
	{
		data->player.angle = data->player.angle - 0.3;
		if (data->player.angle < 0)
			data->player.angle = 359;
	}
}
