/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:10:43 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/13 09:56:14 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	vert_wall(t_data *data, t_ray *ray, double wall_size)
{
	uint32_t	color;

	if (ray->rayDirX > 0)
		color = get_pixel_color(ray->hit \
			- (int)ray->hit, wall_size, data->textures.ea_texture);
	if (ray->rayDirX < 0)
		color = get_pixel_color(ray->hit \
			- (int)ray->hit, wall_size, data->textures.we_texture);
	return (color);
}

double	get_wall_size(t_ray *ray)
{
	double	wall_size;

	if (ray->hip_distance < ray->ver_distance)
		wall_size = (WIDTH / ray->hip_distance);
	else
		wall_size = (WIDTH / ray->ver_distance);
	return (wall_size);
}
