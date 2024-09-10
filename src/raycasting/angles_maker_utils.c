/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:25:07 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/08 13:45:10 by saroca-f         ###   ########.fr       */
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
