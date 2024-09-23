/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:34:44 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/20 16:07:30 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	add_path_to_texture_2(t_data *data, char **path)
{
	if (path[0] && path[1] && !ft_strcmp(path[0], "C"))
	{
		data->textures.c_color = get_color_rgb(path);
		data->textures.c_flag = 1;
	}
	else if (path[0] && path[1] && !ft_strcmp(path[0], "F"))
	{
		data->textures.f_color = get_color_rgb(path);
		data->textures.f_flag = 1;
	}
	else if (path[0] && path[1] && !ft_strcmp(path[0], "DO"))
	{
		data->textures.do_path = ft_strdup(path[1]);
		data->textures.do_flag = 1;
	}
}

void	add_path_to_texture(t_data *data, char **path)
{
	if (path[0] && path[1] && !ft_strcmp(path[0], "NO"))
	{
		data->textures.no_path = ft_strdup(path[1]);
		data->textures.no_flag = 1;
	}
	else if (path[0] && path[1] && !ft_strcmp(path[0], "SO"))
	{
		data->textures.so_path = ft_strdup(path[1]);
		data->textures.so_flag = 1;
	}
	else if (path[0] && path[1] && !ft_strcmp(path[0], "WE"))
	{
		data->textures.we_path = ft_strdup(path[1]);
		data->textures.we_flag = 1;
	}
	else if (path[0] && path[1] && !ft_strcmp(path[0], "EA"))
	{
		data->textures.ea_path = ft_strdup(path[1]);
		data->textures.ea_flag = 1;
	}
	add_path_to_texture_2(data, path);
}

void	ft_load_textures(t_data *data)
{
	data->textures.no_texture = mlx_load_png(data->textures.no_path);
	if (!data->textures.no_texture)
	{
		print_error("Failed to load png for \"NO\"\n");
		exit(FAILURE);
	}
	data->textures.so_texture = mlx_load_png(data->textures.so_path);
	if (!data->textures.so_texture)
	{
		print_error("Failed to load png for \"SO\"\n");
		exit(FAILURE);
	}
	data->textures.we_texture = mlx_load_png(data->textures.we_path);
	if (!data->textures.we_texture)
	{
		print_error("Failed to load png for \"WE\"\n");
		exit(FAILURE);
	}
	data->textures.ea_texture = mlx_load_png(data->textures.ea_path);
	if (!data->textures.ea_texture)
	{
		print_error("Failed to load png for \"EA\"\n");
		exit(FAILURE);
	}
	ft_load_textures_door(data);
}

void	free_textures_memory(t_data *data)
{
	t_texture	t;

	t = data->textures;
	if (t.no_flag)
		free(t.no_path);
	if (t.so_flag)
		free(t.so_path);
	if (t.we_flag)
		free(t.we_path);
	if (t.ea_flag)
		free(t.ea_path);
	if (t.do_flag)
		free(t.do_path);
}

void	ft_delete_textures(t_data *data)
{
	mlx_delete_texture(data->textures.no_texture);
	mlx_delete_texture(data->textures.so_texture);
	mlx_delete_texture(data->textures.we_texture);
	mlx_delete_texture(data->textures.ea_texture);
	if (data->textures.do_flag == 1)
		mlx_delete_texture(data->textures.do_texture);
	if (data->animation.animation_1)
		mlx_delete_texture(data->animation.animation_1);
	if (data->animation.animation_2)
		mlx_delete_texture(data->animation.animation_2);
	if (data->animation.animation_3)
		mlx_delete_texture(data->animation.animation_3);
	if (data->animation.animation_4)
		mlx_delete_texture(data->animation.animation_4);
	if (data->animation.animation_5)
		mlx_delete_texture(data->animation.animation_5);
}
