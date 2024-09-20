/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:04 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/20 16:05:54 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	ft_load_textures_door(t_data *data)
{
	if (data->textures.do_flag == 1)
	{
		data->textures.do_texture = mlx_load_png(data->textures.do_path);
		if (!data->textures.do_texture)
		{
			print_error("Failed to load png for \"DO\"\n");
			exit(FAILURE);
		}
	}
}
