/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:50:11 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/04 16:11:37 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if (check_colors_format(path, line))
		flag = 1;
	if (check_rgb_are_numbers(path, line))
		flag = 1;
	return (flag);
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
	if (path && path[2] && ft_strcmp(path[0], "C")
		&& ft_strcmp(path[0], "F"))
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
