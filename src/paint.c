/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:35:37 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/10 12:05:07 by schamizo         ###   ########.fr       */
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

/*uint32_t	get_wall_color(t_data *data, double wall_pos_x, double wall_pos_y)
{
	//North wall
	if (wall_pos_y > data->player.pos_y)
		return (772233);
	//South Wall
	else if (wall_pos_y < data->player.pos_y)
		return (461713);
	//East Wall
	else if (wall_pos_x > data->player.pos_x)
		return (114356);
	//West Wall
	else if (wall_pos_x < data->player.pos_x)
		return (119999);
	else
		return (0x33333388);
}*/

/*void	paint_column(t_data *data, int j)
{
	uint32_t	wall_color;
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		wall_color = get_wall_color(data, i, j);
		if (i < HEIGHT)
			mlx_put_pixel(data->screen, i, j, wall_color);
		i++;
	}
}

int	painting_everything(t_data *data)
{
	int	i;

	i = 300;
	while (i < WIDTH / 2)
	{
		paint_column(data, i);
		i++;
	}
	return (SUCCESS);
}*/