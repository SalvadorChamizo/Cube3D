/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:00:47 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/02 18:05:28 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ver_pixel_impact(t_ray *ray)
{
	if (ray->rayDirX > 0 && ray->rayDirY > 0)
	{
		ray->pixel_impactX = (ray->mapX) * 64;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
	else if (ray->rayDirX < 0 && ray->rayDirY > 0)
	{
		ray->pixel_impactX = (ray->mapX + 1) * 64;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
	else if (ray->rayDirX > 0 && ray->rayDirY < 0)
	{
		ray->pixel_impactX = (ray->mapX) * 64;
		ray->pixel_impactY = ((ray->mapY) * 64) + ((ray->hit - ray->mapY) * 64);
	}
	else if (ray->rayDirX < 0 && ray->rayDirY < 0)
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

void	cell_impact(t_data *data, t_ray *ray)
{
	ray->mapX = data->player.map_x;
	ray->mapY = data->player.map_y;


	ray->rayDirX = cos(ray->angle);
	ray->rayDirY = sin(ray->angle);


	ray->DeltaDistX = 1 / fabs(ray->rayDirX);
	ray->DeltaDistY = 1 / fabs(ray->rayDirY);


	ray->posX = data->player.pos_x;
	ray->posY = data->player.pos_y;


	if(ray->rayDirX < 0)
		ray->stepX = -1;
	else
		ray->stepX = 1;
	if(ray->rayDirY < 0)
		ray->stepY = -1;
	else
		ray->stepY = 1;


	if (ray->rayDirX > 0)
		ray->sideDistX = (data->player.map_x + ray->stepX - data->player.pos_x) * ray->DeltaDistX;
	else
		ray->sideDistX = (data->player.pos_x - data->player.map_x) * ray->DeltaDistX;
	if (ray->rayDirY > 0)
		ray->sideDistY = (data->player.map_y + ray->stepY - data->player.pos_y) * ray->DeltaDistY;
	else
		ray->sideDistY = (data->player.pos_y - data->player.map_y) * ray->DeltaDistY;


	ray->flag = 0;
	while(data->map.map[ray->mapY][ray->mapX] != '1')
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
		ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
	

	//octavo paso
	if (ray->flag == 0)
		ray->hit = ray->posY + ray->perpWallDist * ray->rayDirY;
	else
		ray->hit = ray->posX + ray->perpWallDist * ray->rayDirX;

	//noveno paso
	
	if (ray->flag == 0)
		ver_pixel_impact(ray);
	else
		hor_pixel_impact(ray);

	//decimo paso
	if (ray->flag == 0)
		ray->distance = sqrt(pow((ray->posX - ray->mapX), 2) + pow((ray->posY - ray->hit), 2));
	else
		ray->distance = sqrt(pow((ray->posX - ray->hit), 2) + pow((ray->posY - ray->mapY), 2));
}

void print_ray(t_data *data, t_player *player)
{
	int i;

	ray_init(data);
	i = 0;
	while (i < WIDTH)
	{
		mlx_put_pixel(data->board, player->ray[i].pixel_impactX, player->ray[i].pixel_impactY, 0xffaa0000);
		cell_impact(data, &player->ray[i]);
		if (i == 960)
		{
			printf ("raydirX: %f\traydirY: %f\n", player->ray[i].rayDirX, player->ray[i].rayDirY);
			printf("HIT: %f\t mapX: %d\tIMPACTO X: %f\tIMPACTO Y: %f\n", player->ray[i].hit, player->ray[i].mapX, player->ray[i].pixel_impactX, player->ray[i].pixel_impactY);
		}
		mlx_put_pixel(data->board, player->ray[i].pixel_impactX, player->ray[i].pixel_impactY, 0xff0000AA);
		i++;
	}
}
