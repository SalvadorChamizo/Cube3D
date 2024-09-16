/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:27:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 11:04:48 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	get_texture_data(t_data *data, int *error_flag, int *fd)
{
	if (fd < 0)
	{
		print_error("Failed to open the map file. ");
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		*error_flag = 1;
		return (*error_flag);
	}
	if (get_wall_textures(data, fd, error_flag))
	{
		*error_flag = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	get_wall_textures(t_data *data, int *fd, int *error_flag)
{
	char	**split_line;
	int		cont;
	int		line_num;

	split_line = NULL;
	cont = 0;
	line_num = 0;
	while (cont < 6)
	{
		if (get_line_and_split(&split_line, *fd))
			return (FAILURE);
		line_num++;
		if (check_texture(data, split_line, &cont, line_num))
			*error_flag = 1;
	}
	check_missing_identifier(data, fd, cont);
	return (SUCCESS);
}

int	get_line_and_split(char ***split_line, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		print_error("Failed reading the line.\n");
		return (FAILURE);
	}
	line = ft_remove_nl(line);
	*split_line = ft_split(line, ' ');
	if (!split_line)
	{
		print_error("Failed in ft_split.\n");
		free(line);
		return (FAILURE);
	}
	free(line);
	return (SUCCESS);
}

int	check_texture(t_data *data, char **path, int *cont, int line)
{
	if (!path[0])
	{
		ft_free_split(path);
		return (SUCCESS);
	}
	if (check_texture_error(path, line))
	{
		add_path_to_texture(data, path);
		ft_free_split(path);
		*cont += 1;
		return (FAILURE);
	}
	add_path_to_texture(data, path);
	ft_free_split(path);
	*cont += 1;
	return (SUCCESS);
}

void	check_missing_identifier(t_data *data, int *fd, int cont)
{
	set_new_fd(data, cont, fd);
	if (data->textures.no_flag != 1)
		print_error("\"NO\" identifier is missing\n");
	if (data->textures.so_flag != 1)
		print_error("\"SO\" identifier is missing\n");
	if (data->textures.we_flag != 1)
		print_error("\"WE\" identifier is missing\n");
	if (data->textures.ea_flag != 1)
		print_error("\"EA\" identifier is missing\n");
	if (data->textures.c_flag != 1)
		print_error("\"C\" identifier is missing\n");
	if (data->textures.f_flag != 1)
		print_error("\"F\" identifier is missing\n");
}
