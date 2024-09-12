/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:48:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/12 11:50:35 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	pack_rgba(uint8_t pixels[4])
{
	uint32_t	color;

	color = 0;
	color |= ((uint32_t)pixels[0] << 24);
	color |= ((uint32_t)pixels[1] << 16);
	color |= ((uint32_t)pixels[2] << 8);
	color |= pixels[3];
	return (color);
}

uint32_t	get_pixel_color(t_data *data, t_ray *ray, int z)
{
	uint32_t	index;
	int			i;
	uint8_t		rgba[4];

	index = ((uint32_t)(z) * data->test->width
		+ (uint32_t)(ray->pixel_width_impact)) * data->test->bytes_per_pixel;
	i = 0;
	while (i < 4)
	{
		rgba[i] = data->test->pixels[index + i];
		i++;
	}
	return (pack_rgba(rgba));
}

uint32_t	get_wall_color(t_data *data, t_ray *ray)
{
	//North wall
	(void)data;
	if (ray->flag == 0)
	{
		if (ray->rayDirX > 0)
		{
			return (0x772233FF);
		}
		if (ray->rayDirX < 0)
			return (0x461713FF);
	}
	else if (ray->flag == 1)
	{
		if (ray->rayDirY > 0)
			return (0x114356FF);
		if (ray->rayDirY < 0)
		return (0x119999FF);
	}
	else
		return (0x33333388);
	return (0x33333388);
}

void    print_wall(t_data *data, t_ray *ray, int x)
{
	double 		wall_size;
	uint32_t	color;
	int 		i;
	int			first_pixel;

	i = 0;
	if (ray->hip_distance < ray->ver_distance)
		wall_size = (HEIGHT / ray->hip_distance);
	else
		wall_size = (HEIGHT / ray->ver_distance); 
	first_pixel = ((HEIGHT / 2) - (wall_size / 2));
	if (first_pixel < 0)
		first_pixel = 0;
	while(i < HEIGHT)
	{
		if (i == 640 && (x == 490 || x == 960 || x == 1350))
		{
			if (x == 490)
				printf(RED"Izquierda\n");
			else if (x == 960)
				printf(GREEN"Centro\n");
			else if (x == 1350)
				printf(BLUE"Derecha\n");
			printf("ray->angle = %f\n", ray->angle);
			printf("data->player.angle = %f\n", data->player.angle * (M_PI / 180));
			printf("ray->hip_distance = %f\n", ray->hip_distance);
			printf("ray->ver_distance = %f\n", ray->ver_distance);
			printf("wall_size = %f\n", wall_size);
			printf("first_pixel = %d\n", first_pixel);
		}
		color = get_wall_color(data, ray);
		if (i >= first_pixel && i < first_pixel + wall_size)
		{
			//if (x >= 950  && x <= 970)
			//	mlx_put_pixel(data->board, x,  i, 255);
			mlx_put_pixel(data->board, x,  i, color);
		}
		i++;
	}
}