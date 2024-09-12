/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:00:47 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/12 12:29:06 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_color(t_data *data, t_ray *ray, int x);

void	ray_var_init(t_data *data, t_ray *ray)
{
	ray->mapX = data->player.map_x;
	ray->mapY = data->player.map_y;
	ray->rayDirX = cos(ray->angle);
	ray->rayDirY = sin(ray->angle);
	ray->DeltaDistX = 1 / fabs(ray->rayDirX);
	ray->DeltaDistY = 1 / fabs(ray->rayDirY);
	ray->posX = data->player.pos_x;
	ray->posY = data->player.pos_y;
	ray->stepX = 0;
	ray->stepY = 0;
	if (ray->rayDirX < 0)
		ray->stepX = -1;
	else
		ray->stepX = 1;
	if (ray->rayDirY < 0)
		ray->stepY = -1;
	else
		ray->stepY = 1;
	ray->flag = 0;
}

void	sidedist(t_data *data, t_ray *ray)
{
	if (ray->rayDirX > 0)
		ray->sideDistX = (data->player.map_x + ray->stepX - data->player.pos_x) * ray->DeltaDistX;
	else
		ray->sideDistX = (data->player.pos_x - data->player.map_x) * ray->DeltaDistX;
	if (ray->rayDirY > 0)
		ray->sideDistY = (data->player.map_y + ray->stepY - data->player.pos_y) * ray->DeltaDistY;
	else
		ray->sideDistY = (data->player.pos_y - data->player.map_y) * ray->DeltaDistY;
}

void	dda_bucle(t_data *data, t_ray *ray)
{
	while (data->map.map[ray->mapY][ray->mapX] != '1')
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->DeltaDistX;
			ray->mapX += ray->stepX;
			ray->flag = 0;
		}
		else
		{
			ray->sideDistY += ray->DeltaDistY;
			ray->mapY += ray->stepY;
			ray->flag = 1;
		}
	}
	if (ray->flag == 0)
		ray->perpWallDist = (ray->mapX - ray->posX + \
			(1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - ray->posY + \
			(1 - ray->stepY) / 2) / ray->rayDirY;
}

void   get_ver_distance(t_data *data, t_ray *ray, int i)
{
	double	player_angle;	
	double	dif_angle;

	player_angle = data->player.angle * (M_PI / 180);
	dif_angle = fabs(ray->angle_ret - player_angle);
	if (dif_angle > M_PI)
		dif_angle = 2 * M_PI - dif_angle;
	//double adjusted_angle = fabs(M_PI / 2 - dif_angle);
	if (i == 490 || i == 960 || i == 1350)
	ray->ver_distance = ray->hip_distance * cos(dif_angle);
    if (ray->ver_distance < 0.0001)
        ray->ver_distance = 9999999999999.0;
}

//jesumore  meter en slack

void	cell_impact(t_data *data, t_ray *ray, int i)
{
	ray_var_init(data, ray);
	sidedist(data, ray);
	dda_bucle(data, ray);
	if (ray->flag == 0)
		ray->hit = ray->posY + (ray->perpWallDist * ray->rayDirY);
	else
		ray->hit = ray->posX + (ray->perpWallDist * ray->rayDirX);
	if (ray->flag == 0)
		ver_pixel_impact(ray);
	else
		hor_pixel_impact(ray);
	if (ray->flag == 0 && ray->rayDirX > 0)
		ray->hip_distance = sqrt(pow((ray->mapX - ray->posX), 2) + pow((ray->hit - ray->posY), 2));
	else if (ray->flag == 0 && ray->rayDirX < 0)
		ray->hip_distance = sqrt(pow(((ray->mapX + 1) - ray->posX), 2) + pow((ray->hit - ray->posY), 2));
	else if ( ray->flag == 1 && ray->rayDirY > 0)
		ray->hip_distance = sqrt(pow((ray->hit - ray->posX), 2) + pow((ray->mapY - ray->posY), 2));
	else
		ray->hip_distance = sqrt(pow((ray->hit - ray->posX), 2) + pow(((ray->mapY + 1) - ray->posY), 2));
	get_ver_distance(data, ray, i);
}

void	print_ray(t_data *data, t_player *player)
{
	int	i;

	ray_init(data);
	i = 0;
	while (i < WIDTH)
	{
		cell_impact(data, &player->ray[i], i);
		print_wall(data, &player->ray[i], i);
		i++;
	}
}
