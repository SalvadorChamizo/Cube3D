/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:10:43 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/13 12:36:57 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_wall_size(t_ray *ray)
{
	double	wall_size;

	if (ray->hip_distance < ray->ver_distance)
		wall_size = (WIDTH / ray->hip_distance);
	else
		wall_size = (WIDTH / ray->ver_distance);
	return (wall_size);
}
