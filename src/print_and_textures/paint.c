/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:35:37 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/13 09:58:59 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
				mlx_put_pixel(data->screen, w, h++, data->textures.c_color);
			else
				mlx_put_pixel(data->screen, w, h++, data->textures.f_color);
		}
		w++;
	}
	return (SUCCESS);
}
