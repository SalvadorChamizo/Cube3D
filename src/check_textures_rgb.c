/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_rgb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:42:56 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:40 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	get_color_rgb(char **path)
{
	unsigned int	color;

	if (ft_split_size(path) == 2)
	{
		color = get_color_rgb_two_args(path);
		if (color == 1)
			color = 255;
	}
	if (ft_split_size(path) == 4)
	{
		color = get_color_rgb_four_args(path);
		if (color == 1)
			color = 255;
	}
	return (color);
}

unsigned int	get_color_rgb_two_args(char **path)
{
	char			**rgb;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	color;

	rgb = ft_split(path[1], ',');
	if (!rgb)
	{
		print_error("Failed in ft_split.\n");
		return (FAILURE);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (r > 255 || g > 255 || b > 255)
	{
		error_rgb_value(path, r, g, b);
		return (FAILURE);
	}
	color = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (color);
}

unsigned int	get_color_rgb_four_args(char **path)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	color;

	if (!path || !path[0] || !path[1] || !path[2] || !path[3])
		return (FAILURE);
	r = ft_atoi(path[1]);
	g = ft_atoi(path[2]);
	b = ft_atoi(path[3]);
	if (r > 255 || g > 255 || b > 255)
	{
		error_rgb_value(path, r, g, b);
		return (FAILURE);
	}
	color = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (color);
}

void	error_rgb_value(char **path, int r, int g, int b)
{
	print_error("Invalid rgb value for ");
	ft_putstr_fd(path[0], 2);
	ft_putstr_fd(". ", 2);
	if (r > 255)
	{
		ft_putstr_fd("r = ", 2);
		ft_putnbr_fd(r, 2);
		ft_putstr_fd(". ", 2);
	}
	if (g > 255)
	{
		ft_putstr_fd("g = ", 2);
		ft_putnbr_fd(g, 2);
		ft_putstr_fd(". ", 2);
	}
	if (b > 255)
	{
		ft_putstr_fd("b = ", 2);
		ft_putnbr_fd(b, 2);
		ft_putstr_fd(". ", 2);
	}
	ft_putstr_fd("Using color black.\n", 2);
}

int	check_rgb_are_numbers(char **color, int line)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strcmp(color[0], "F") && ft_strcmp(color[0], "C"))
		return (SUCCESS);
	while (color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]) && color[i][j] != ',')
			{
				rgb_error_not_number(color, i, j, line);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}
