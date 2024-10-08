/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:48:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/14 18:31:44 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	get_pixel_color(double ratio_x, \
double wall_size, mlx_texture_t *texture)
{
	uint32_t		index;
	uint8_t			rgba[4];
	unsigned int	i;

	i = 0;
	if (!texture || !texture->pixels || ratio_x >= 1 || wall_size >= 1)
		return (0);
	index = ((uint32_t)(texture->height * wall_size) * texture->width
			+ (uint32_t)(texture->width * ratio_x)) * texture->bytes_per_pixel;
	while (i < 4)
	{
		rgba[i] = texture->pixels[index + i];
		i++;
	}
	return (pack_rgba(rgba));
}

uint32_t	get_wall_color(t_data *data, t_ray *ray, double wall_size)
{
	uint32_t	color;

	if (ray->flag == 0)
	{
		if (ray->ray_dir_x > 0)
			color = get_pixel_color(ray->hit \
				- (int)ray->hit, wall_size, data->textures.ea_texture);
		if (ray->ray_dir_x < 0)
			color = get_pixel_color(ray->hit \
				- (int)ray->hit, wall_size, data->textures.we_texture);
		return (color);
	}
	else if (ray->flag == 1)
	{
		if (ray->ray_dir_y > 0)
			color = get_pixel_color(ray->hit \
				- (int)ray->hit, wall_size, data->textures.so_texture);
		if (ray->ray_dir_y < 0)
			color = get_pixel_color(ray->hit \
				- (int)ray->hit, wall_size, data->textures.no_texture);
		return (color);
	}
	return (0x33333388);
}

void	print_wall_column(t_data *data, t_ray *ray, int x)
{
	double		wall_size;
	uint32_t	color;
	int			i;
	int			first_pixel;
	int			save_pixel;

	i = 0;
	save_pixel = 0;
	wall_size = get_wall_size(ray);
	first_pixel = ((HEIGHT / 2) - (wall_size / 2));
	if (first_pixel < 0)
	{
		save_pixel = -first_pixel;
		first_pixel = 0;
	}
	while (i < HEIGHT)
	{
		if (i > first_pixel && i < HEIGHT - 1)
		{
			color = get_wall_color(data, ray, \
				(i - first_pixel + save_pixel) / wall_size);
			mlx_put_pixel(data->walls, x, i, color);
		}
		i++;
	}
}
