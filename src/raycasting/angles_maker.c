/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:00:47 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/13 19:35:13 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_side_distance(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x > 0)
		ray->side_dist_x = (data->player.map_x + \
			ray->step_x - data->player.pos_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (data->player.pos_x - \
			data->player.map_x) * ray->delta_dist_x;
	if (ray->ray_dir_y > 0)
		ray->side_dist_y = (data->player.map_y + \
			ray->step_y - data->player.pos_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (data->player.pos_y - \
			data->player.map_y) * ray->delta_dist_y;
}

void	dda_loop(t_data *data, t_ray *ray)
{
	while (data->map.map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->flag = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->flag = 1;
		}
	}
	if (ray->flag == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + \
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + \
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	calculate_vertical_distance(t_data *data, t_ray *ray)
{
	double	player_angle;	
	double	dif_angle;

	player_angle = data->player.angle * (M_PI / 180);
	dif_angle = fabs(ray->angle_ret - player_angle);
	if (dif_angle > M_PI)
		dif_angle = 2 * M_PI - dif_angle;
	ray->ver_distance = ray->hyp_distance * cos(dif_angle);
	if (ray->ver_distance < 0.0001)
		ray->ver_distance = 9999999999999.0;
}

void	find_ray_hit_point(t_data *data, t_ray *ray)
{
	init_ray_variables(data, ray);
	calculate_side_distance(data, ray);
	dda_loop(data, ray);
	if (ray->flag == 0)
		ray->hit = ray->pos_y + (ray->perp_wall_dist * ray->ray_dir_y);
	else
		ray->hit = ray->pos_x + (ray->perp_wall_dist * ray->ray_dir_x);
	if (ray->flag == 0)
		ver_pixel_impact(ray);
	else
		hor_pixel_impact(ray);
	calculate_hypotenuse_distance(ray);
	calculate_vertical_distance(data, ray);
}

void	print_ray(t_data *data, t_player *player)
{
	int	i;

	ray_init(data);
	i = 0;
	while (i < WIDTH)
	{
		find_ray_hit_point(data, &player->ray[i]);
		print_wall_column(data, &player->ray[i], i);
		i++;
	}
}
