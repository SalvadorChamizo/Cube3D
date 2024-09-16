/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:10:43 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/16 11:05:10 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

double	get_wall_size(t_ray *ray)
{
	double	wall_size;

	if (ray->hyp_distance < ray->ver_distance)
		wall_size = (WIDTH / ray->hyp_distance);
	else
		wall_size = (WIDTH / ray->ver_distance);
	return (wall_size);
}

uint32_t	pack_rgba(uint8_t pixels[4])
{
	uint32_t	color;

	color = 0;
	color |= ((uint32_t)pixels[0] << 24);
	color |= ((uint32_t)pixels[1] << 16);
	color |= ((uint32_t)pixels[2] << 8);
	color |= pixels[3];
	return (color);
}
