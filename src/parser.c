/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:38:05 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/23 19:00:11 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map_extension(char *file, int *error_flag)
{
	char	*extension;

	if (!file)
		return (1);
	extension = ft_strrchr(file, '.');
	if (!extension || ft_strlen(extension) != 4 || ft_strcmp(extension, ".cub"))
	{
		print_error("Wrong map extension \"");
		ft_putstr_fd(extension, 2);
		ft_putstr_fd("\"\n", 2);
		*error_flag = 1;
	}
	return (*error_flag);
}

/*int	check_map_permissions()*/

int	assign_texture(t_data *data, char **path)
{
	(void) data;
	if (strcmp(path[0], "NO") && strcmp(path[0], "SO")
		&& strcmp(path[0], "WE") && strcmp(path[0], "EA")
		&& strcmp(path[0], "F") && strcmp(path[0], "C"))
	{
		print_error("Not valid identifier in map: \"");
		ft_putstr_fd(path[0], 2);
		ft_putstr_fd("\"\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_identifier_error(char **path, int line)
{
	if (ft_strcmp(path[0], "NO") && ft_strcmp(path[0], "SO")
		&& ft_strcmp(path[0], "WE") && ft_strcmp(path[0], "EA")
		&& ft_strcmp(path[0], "F") && ft_strcmp(path[0], "C"))
	{
		print_error("Not valid identifier in line ");
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": \"", 2);
		ft_putstr_fd(path[0], 2);
		ft_putstr_fd("\"\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_missing_path(char **path, int line)
{
	if (!path[1])
	{
		print_error("Wrong texture format in line ");
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(". Missing path.\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_extra_argument(char **path, int line)
{
	if (path[2])
	{
		print_error("Extra argument in line ");
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": \"", 2);
		ft_putstr_fd(path[2], 2);
		ft_putstr_fd("\"\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_texture_permission(char *name, char *texture, int line)
{
	int	fd;

	if (!ft_strcmp(name, "C") || !ft_strcmp(name, "F"))
		return (SUCCESS);
	fd = open(texture, O_RDONLY);
	if (fd < 0)
	{
		print_error("Failed to open the texture file from line ");
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(". ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	check_texture_error(char **path, int line)
{
	int	flag;

	flag = 0;
	if (check_identifier_error(path, line))
		flag = 1;
	if (check_missing_path(path, line))
		flag = 1;
	if (check_extra_argument(path, line))
		flag = 1;
	if (check_texture_permission(path[0], path[1], line))
		flag = 1;
	return (flag);
}

int	check_texture(t_data *data, char **path, int *cont, int line)
{
	(void) data;
	if (!path[0])
	{
		ft_free_split(path);
		return (SUCCESS);
	}
	check_texture_error(path, line);
	if (path[0] && path[1] && !ft_strcmp(path[0], "NO"))
		data->textures.no_path = ft_strdup(path[1]);
	else if (path[0] && path[1] && !ft_strcmp(path[0], "SO"))
		data->textures.so_path = ft_strdup(path[1]);
	else if (path[0] && path[1] && !ft_strcmp(path[0], "WE"))
		data->textures.we_path = ft_strdup(path[1]);
	else if (path[0] && path[1] && !ft_strcmp(path[0], "EA"))
		data->textures.ea_path = ft_strdup(path[1]);
	else if (path[0] && path[1] && !ft_strcmp(path[0], "C"))
		data->textures.c_color = ft_strdup(path[1]);
	else if (path[0] && path[1] && !ft_strcmp(path[0], "F"))
		data->textures.f_color = ft_strdup(path[1]);
	ft_free_split(path);
	*cont += 1;
	return (SUCCESS);
}

int	check_wall_textures(t_data *data, int fd, int *error_flag)
{
	char	*line;
	char	**split_line;
	int		cont;
	int		line_num;

	cont = 0;
	(void) error_flag;
	line_num = 0;
	while (cont < 6)
	{
		line = get_next_line(fd);
		line_num++;
		if (!line)
		{
			print_error("Failed reading the line.\n");
			return (FAILURE);
		}
		line = ft_remove_nl(line);
		split_line = ft_split(line, ' ');
		if (!split_line)
		{
			print_error("Failed in ft_split.\n");
			return (FAILURE);
		}
		free(line);
		if (check_texture(data, split_line, &cont, line_num))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_map_data(char *file, t_data *data, int *error_flag)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error("Failed to open the map file. ");
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		*error_flag = 1;
		return (*error_flag);
	}
	if (check_wall_textures(data, fd, error_flag))
	{
		*error_flag = 1;
		return (FAILURE);
	}
	return (0);
}

int	parse_map(char *file, t_data *data)
{
	int	error_flag;

	error_flag = 0;
	check_map_extension(file, &error_flag);
	check_map_data(file, data, &error_flag);
	return (error_flag);
}
