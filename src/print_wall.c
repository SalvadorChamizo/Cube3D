/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:48:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/12 12:13:17 by schamizo         ###   ########.fr       */
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

uint32_t	get_pixel_color(double ratio_x, double wall_size, mlx_texture_t *texture)
{
	uint32_t		index;
	uint8_t			rgba[4];
	unsigned int	i;

	//printf("%f\n%f\n", ratio_x, wall_size);
	if (!texture || !texture->pixels || ratio_x >= 1 || wall_size >= 1)
		return (0);
	index = ((uint32_t)(texture->height * wall_size) * texture->width
			+ (uint32_t)(texture->width * ratio_x))
		* texture->bytes_per_pixel;
	i = 0;
	while (i < 4)
	{
		rgba[i] = texture->pixels[index + i];
		i++;
	}
	return (pack_rgba(rgba));
}

uint32_t	get_wall_color(t_data *data, t_ray *ray, double wall_size)
{
	//North wall
	(void)data;
	uint32_t	color;
	//printf("%f\n", wall_size);
	if (ray->flag == 0)
	{
		if (ray->rayDirX > 0)
		{
			color = get_pixel_color(ray->hit - (int)ray->hit, wall_size, data->textures.no_texture);
			return (color);
			//return (0x772233FF);
		}
		if (ray->rayDirX < 0)
		{
			color = get_pixel_color(ray->hit - (int)ray->hit, wall_size, data->textures.so_texture);
			return (color);
			//return (0x461713FF);
		}
	}
	else if (ray->flag == 1)
	{
		if (ray->rayDirY > 0)
		{
			color = get_pixel_color(ray->hit - (int)ray->hit, wall_size, data->textures.we_texture);
			return (color);
			//return (0x114356FF);
		}
		if (ray->rayDirY < 0)
		{
			color = get_pixel_color(ray->hit - (int)ray->hit, wall_size, data->textures.ea_texture);
			return (color);
			//return (0x119999FF);
		}
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
	wall_size = (WIDTH / ray->distance);
	//wall_size = (HEIGHT / ray->distance);
	first_pixel = ((HEIGHT / 2) - (wall_size / 2));
	if (first_pixel < 0)
		first_pixel = 0;
	while(i < HEIGHT)
	{
		if (i > first_pixel && i < first_pixel + wall_size)
		{
			//printf("%f\n", wall_size);
			color = get_wall_color(data, ray, (i - first_pixel) / wall_size);
			mlx_put_pixel(data->board, x,  i, color);
		}
		i++;
	}
}