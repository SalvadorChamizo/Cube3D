/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:25:07 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/18 10:17:17 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	ver_pixel_impact(t_ray *ray)
{
		ray->pixel_width_impact = (ray->hit - ray->map_y) * 1920;
}

void	hor_pixel_impact(t_ray *ray)
{
		ray->pixel_width_impact = (ray->hit - ray->map_x) * 1920;
}

void	init_ray_variables(t_data *data, t_ray *ray)
{
	ray->map_x = data->player.map_x;
	ray->map_y = data->player.map_y;
	ray->ray_dir_x = cos(ray->angle);
	ray->ray_dir_y = sin(ray->angle);
	ray->delta_dist_x = 1 / fabs(ray->ray_dir_x);
	ray->delta_dist_y = 1 / fabs(ray->ray_dir_y);
	ray->pos_x = data->player.pos_x;
	ray->pos_y = data->player.pos_y;
	ray->step_x = 0;
	ray->step_y = 0;
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	ray->flag = 0;
	ray->door_flag = 0;
}

void	calculate_hypotenuse_distance(t_ray *ray)
{
	if (ray->flag == 0 && ray->ray_dir_x > 0)
		ray->hyp_distance = sqrt(pow((ray->map_x - \
			ray->pos_x), 2) + pow((ray->hit - ray->pos_y), 2));
	else if (ray->flag == 0 && ray->ray_dir_x < 0)
		ray->hyp_distance = sqrt(pow(((ray->map_x + 1) - \
			ray->pos_x), 2) + pow((ray->hit - ray->pos_y), 2));
	else if (ray->flag == 1 && ray->ray_dir_y > 0)
		ray->hyp_distance = sqrt(pow((ray->hit - \
			ray->pos_x), 2) + pow((ray->map_y - ray->pos_y), 2));
	else
		ray->hyp_distance = sqrt(pow((ray->hit - \
			ray->pos_x), 2) + pow(((ray->map_y + 1) - ray->pos_y), 2));
}
