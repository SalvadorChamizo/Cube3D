/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:57:27 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/06 17:40:11 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	angle_select(t_data *data, char c)
{
	if (c == 'N')
		data->player.angle = 270;
	if (c == 'S')
		data->player.angle = 90;
	if (c == 'W')
		data->player.angle = 180;
	if (c == 'E')
		data->player.angle = 0;
}

void	ray_init(t_data *data)
{
	double	fov_rad;
	double	angle_rad;
	int 	i;

	fov_rad = FOV * M_PI / 180;
	angle_rad = data->player.angle * M_PI / 180;
	i = 0;
	while (i < WIDTH)
	{
		data->player.ray[i].angle = angle_rad - (fov_rad / 2) + ((fov_rad / WIDTH) * i);
		if (data->player.ray[i].angle < 0)
			data->player.ray[i].angle += 2 * M_PI;
		i++;
	}
}
