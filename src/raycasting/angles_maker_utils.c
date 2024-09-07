/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:25:07 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/07 17:54:37 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ver_pixel_impact(t_ray *ray)
{
	if (ray->rayDirX > 0 && ray->rayDirY >= 0)
	{
		ray->pixel_impactX = (ray->mapX) * 64;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
	else if (ray->rayDirX <= 0 && ray->rayDirY > 0)
	{
		ray->pixel_impactX = (ray->mapX + 1) * 64;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
	else if (ray->rayDirX >= 0 && ray->rayDirY < 0)
	{
		ray->pixel_impactX = (ray->mapX) * 64;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
	else if (ray->rayDirX < 0 && ray->rayDirY <= 0)
	{
		ray->pixel_impactX = (ray->mapX + 1) * 64.0;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
}

void	hor_pixel_impact(t_ray *ray)
{
	if (ray->rayDirX > 0 && ray->rayDirY >= 0)
	{
		ray->pixel_impactX = ((ray->mapX) * 64) + ((ray->hit - ray->mapX) * 64);
		ray->pixel_impactY = (ray->mapY) * 64;
	}
	else if (ray->rayDirX <= 0 && ray->rayDirY > 0)
	{
		ray->pixel_impactX = ((ray->mapX) * 64) + ((ray->hit - ray->mapX) * 64);
		ray->pixel_impactY = (ray->mapY) * 64;
	}
	else if (ray->rayDirX >= 0 && ray->rayDirY < 0)
	{
		ray->pixel_impactX = ((ray->mapX) * 64) + ((ray->hit - ray->mapX) * 64);
		ray->pixel_impactY = (ray->mapY + 1) * 64;
	}
	else if (ray->rayDirX < 0 && ray->rayDirY <= 0)
	{
		ray->pixel_impactX = ((ray->mapX) * 64) + ((ray->hit - ray->mapX) * 64);
		ray->pixel_impactY = (ray->mapY + 1) * 64;
	}
}
