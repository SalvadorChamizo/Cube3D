/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:25:57 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/08 14:00:35 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*void	bucle_print_ray(t_data *data, t_ray *ray, float *x, float *y)
{
	if (fabs(ray->xincrement) < (data->map.map_size_x * 64))
	{
		if (ray->pixel_impactX > *x)
			*x += ray->xincrement;
		else
			*x -= ray->xincrement;
	}
	if (fabs(ray->yincrement) < (data->map.map_size_y * 64))
	{
		if (ray->pixel_impactY > *y)
			*y += ray->yincrement;
		else
			*y -= ray->yincrement;
	}
	mlx_put_pixel(data->board, round(*x), round(*y), 0xff0000AA);
}

void	print_one_ray(t_data *data, t_ray *ray)
{
	float	x;
	float	y;
	int		steps;
	int		i;

	x = (data->player.pos_x * 64);
	y = (data->player.pos_y * 64);
	ray->difx = fabs(ray->pixel_impactX - x);
	ray->dify = fabs(ray->pixel_impactY - y);
	if (ray->difx > ray->dify)
		steps = ray->difx;
	else
		steps = ray->dify;
	ray->xincrement = ray->difx / (double)steps;
	ray->yincrement = ray->dify / (double)steps;
	i = 0;
	while (i < steps && x > 0 && y > 0)
	{
		bucle_print_ray(data, ray, &x, &y);
		i++;
	}
}*/
