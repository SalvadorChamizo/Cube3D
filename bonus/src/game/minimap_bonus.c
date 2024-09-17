/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:15:57 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/17 18:28:43 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

bool	check_wall(t_data *data, int x, int y)
{
	double		map_x;
	double		map_y;

	map_x = (data->player.pos_x - 2.5) + ((double)x / 64);
	map_y = (data->player.pos_y - 2.5) + ((double)y / 64);
	if (map_x < 0 || map_y < 0)
		return (false);
	if (map_x >= data->map.map_size_x || map_y >= data->map.map_size_y)
		return (false);
	if (data->map.map[(int)map_y][(int)map_x] == '1')
		return (true);
	return (false);
}

bool	check_point(int x, int y)
{
	int cx = 160;
    int cy = 160;
    int r = 16;

	if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
		return (true);
	return (false);
}

void	cono_printer(t_data *data, t_ray *ray)
{
	double	x;
	double	y;	

	x = 160;
	y = 160;
	while(check_point((int)(y), (int)(x)))
	{
		//if (check_point((int)(data->player.pos_y + y), (int)(data->player.pos_x + x)))
		mlx_put_pixel(data->walls, (int)x, (int)y, 0xFF000088);
		x += ray->ray_dir_x;
		y += ray->ray_dir_y;
	}
}

void    make_minimap(t_data *data)
{
	int x = 0;
	int y = 0;
	int i = 0;

	while (y < 320)
	{
		x = 0;
		while(x < 320)
		{
			if (check_wall(data, x, y))
				mlx_put_pixel(data->walls, x, y, 0xFF00FF88);
			else if (check_point(x, y))
				mlx_put_pixel(data->walls, x, y, 0x00FF0088);
			x++;
		}
		y++;
	}
	while (i < 1920)
	{
		cono_printer(data, &data->player.ray[i]);
		i++;
	}
}