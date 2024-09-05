/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:00:47 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/05 16:39:12 by schamizo         ###   ########.fr       */
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

void	print_one_ray(t_data *data, t_ray *ray, uint32_t color)
{
	float x;
	float y;
	int steps;
	int i;

 	x = (data->player.pos_x * 64);
	y = (data->player.pos_y * 64);
	ray->difx = fabs(ray->pixel_impactX - x);
	ray->dify = fabs(ray->pixel_impactY - y);
	if (ray->difx > ray->dify)
		steps = ray->difx;
	else
		steps = ray->dify;
	ray->xincrement = ray->difx / (double)steps;
	ray->yincrement = ray->dify / (double)steps;
	i = 0;
	while (i < steps && x > 0 && y > 0)
	{
		if(fabs(ray->xincrement) < (data->map.map_size_x * 64))
		{
			if (ray->pixel_impactX > x)
				x += ray->xincrement;
			else
				x -= ray->xincrement;
		}
		if (fabs(ray->yincrement) < (data->map.map_size_y * 64))
		{
			if (ray->pixel_impactY > y)
				y += ray->yincrement;
			else
				y -= ray->yincrement;
		}
		i++;
		if (round(x) >= 64 * data->map.map_size_x || round(y) >= 64 * data->map.map_size_y || round(x) <= 0 || round(y) <= 0)
		{
			printf("x:      %f  y:      %f\n", x, y);
			printf("pixelx: %f  pixely: %f\n", ray->pixel_impactX, ray->pixel_impactY);
			printf("rayDirX:%f  RayDirY:%f\n", ray->rayDirX, ray->rayDirY);
			printf("Deltax: %f  Deltay: %f\n", ray->DeltaDistX, ray->DeltaDistY);
			printf("mapX:   %d  mapY:   %d\n", ray->mapX, ray->mapY);
			printf("posx:   %f  posy:   %f\n", ray->posX, ray->posY);
		}
		if (!data->board)
			printf("board is null\n");
		mlx_put_pixel(data->board, x, y, color);
		//mlx_put_pixel(data->board, round(x), round(y), 0xffaa0000); //borrar
	}
}

void print_ray(t_data *data, t_player *player)
{
	int i;

	data->board = mlx_new_image(data->mlx, data->map.map_size_x * 64, data->map.map_size_y * 64);
	mlx_image_to_window(data->mlx, data->board, 0, 0);
	ray_init(data);
	i = 0;
	while (i < WIDTH)
	{
		cell_impact(data, &player->ray[i]);
		print_one_ray(data, &player->ray[i], 0xff0000AA);
		i++;
	}
}
