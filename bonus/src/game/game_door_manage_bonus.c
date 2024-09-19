/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_door_manage_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:46:42 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/19 11:28:25 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	door_dda_loop(t_data *data, t_ray *ray)
{
	while (data->map.map[ray->map_y][ray->map_x] != '1' &&
		data->map.map[ray->map_y][ray->map_x] != 'D' &&
		data->map.map[ray->map_y][ray->map_x] != 'C')
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

bool	check_door(t_data *data)
{
	int check_x;
	int check_x2;
	int check_y;
	int check_y2;

	check_x = (int)floor((data->player.pos_x + 0.25));
	check_x2 = (int)floor((data->player.pos_x - 0.25));
	check_y = (int)floor((data->player.pos_y + 0.25));
	check_y2 = (int)floor((data->player.pos_y - 0.25));
	if (data->map.map[check_y][check_x] == 'C')
		return (false);
	if (data->map.map[check_y2][check_x] == 'C')
		return (false);
	if (data->map.map[check_y][check_x2] == 'C')
		return (false);
	if (data->map.map[check_y2][check_x2] == 'C')
		return (false);
	return (true);
}

void	door_manage(t_data *data)
{
	t_ray		door_ray;

	if (!check_door(data))
		return ;
	door_ray.angle = data->player.angle * (M_PI / 180);
	init_ray_variables(data, &door_ray);
	calculate_side_distance(data, &door_ray);
	door_dda_loop(data, &door_ray);
	if (door_ray.flag == 0)
		door_ray.hit = door_ray.pos_y + (door_ray.perp_wall_dist * door_ray.ray_dir_y);
	else
		door_ray.hit = door_ray.pos_x + (door_ray.perp_wall_dist * door_ray.ray_dir_x);
	if (door_ray.flag == 0)
		ver_pixel_impact(&door_ray);
	else
		hor_pixel_impact(&door_ray);
	calculate_hypotenuse_distance(&door_ray);
	printf("hyp_distance: %f\n", door_ray.hyp_distance);
	if (data->map.map[door_ray.map_y][door_ray.map_x] == 'D' && door_ray.hyp_distance <= 1)
		data->map.map[door_ray.map_y][door_ray.map_x] = 'C';
	else if (data->map.map[door_ray.map_y][door_ray.map_x] == 'C' && door_ray.hyp_distance <= 1)
		data->map.map[door_ray.map_y][door_ray.map_x] = 'D';
}
