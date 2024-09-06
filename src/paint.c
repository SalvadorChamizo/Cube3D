/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:35:37 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/06 11:33:05 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int paint_floor_ceiling(t_data *data)
{
    int w;
    int h;

	w = 0;
	while (w < WIDTH)
    {
		h = 0;
		while (h < HEIGHT) 
        {
			if (h < HEIGHT / 2)
				mlx_put_pixel(data->screen, w, h++, data->textures.f_color);
			else
				mlx_put_pixel(data->screen, w, h++, data->textures.c_color);
		}
		w++;
	}
    return (SUCCESS);
}

uint32_t	paint_wall(t_data *data)
{
	//North wall
	if (pfv.wall_y > data->player.pos_y)
		return (get_colour_from_texture(1 - pfv.wall_x + (int)pfv.wall_x, calc_h, data->textures.no_texture));
	//South Wall
	else if (pfv.wall_y < data->player.pos_y)
		return (get_colour_from_texture(pfv.wall_x - (int)pfv.wall_x, calc_h, data->textures.so_texture));
	//East Wall
	else if (pfv.wall_x > data->player.pos_x)
		return (get_colour_from_texture(pfv.wall_y - (int)pfv.wall_y, calc_h, data->textures.ea_texture));
	//West Wall
	else if (pfv.wall_x < data->player.pos_x)
		return (get_colour_from_texture(1 - pfv.wall_y + (int)pfv.wall_y, calc_h, data->textures.we_texture));
	else
		return (0x33333388);
}