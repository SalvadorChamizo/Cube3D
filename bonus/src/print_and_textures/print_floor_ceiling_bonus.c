/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floor_ceiling_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:35:37 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 11:05:02 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	paint_floor_ceiling(t_data *data)
{
	int	w;
	int	h;

	w = 0;
	while (w < WIDTH)
	{
		h = 0;
		while (h < HEIGHT)
		{
			if (h < HEIGHT / 2)
				mlx_put_pixel(data->background, w, h++, data->textures.c_color);
			else
				mlx_put_pixel(data->background, w, h++, data->textures.f_color);
		}
		w++;
	}
	return (SUCCESS);
}
