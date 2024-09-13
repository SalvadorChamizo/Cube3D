/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:25:07 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/12 17:58:19 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ver_pixel_impact(t_ray *ray)
{
	if (ray->rayDirX > 0 && ray->rayDirY >= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapY) * 1920;
	}
	else if (ray->rayDirX <= 0 && ray->rayDirY > 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapY) * 1920;
	}
	else if (ray->rayDirX >= 0 && ray->rayDirY < 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapY) * 1920;
	}
	else if (ray->rayDirX < 0 && ray->rayDirY <= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapY) * 1920;
	}
}

void	hor_pixel_impact(t_ray *ray)
{
	if (ray->rayDirX > 0 && ray->rayDirY >= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapX) * 1920;
	}
	else if (ray->rayDirX <= 0 && ray->rayDirY > 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapX) * 1920;
	}
	else if (ray->rayDirX >= 0 && ray->rayDirY < 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapX) * 1920;
	}
	else if (ray->rayDirX < 0 && ray->rayDirY <= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->mapX) * 1920;
	}
}

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
