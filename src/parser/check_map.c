/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:21:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/12 19:34:57 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ft_putstr_fd("\". The extension must be \".cub\"\n", 2);
		*error_flag = 1;
	}
	return (*error_flag);
}

int	check_first_last_line(t_data *data, char **map)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (check_first_line(map))
		flag = 1;
	if (check_last_line(map, data->map.map_line))
		flag = 1;
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}

int	check_invalid_character(char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (c != 'N' && c != 'S' && c != 'W'
		&& c != 'E' && c != ' ' && c != '1'
		&& c != '0' && c != '\n')
	{
		return (1);
	}
	return (0);
}

int	check_middle_lines(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_invalid_character(map[i][j]))
			{
				error_invalid_char(map, i, j);
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

int	check_map_is_closed(t_data *data)
{
	int	flag;

	flag = 0;
	if (check_side_walls(data->map.map))
		flag = 1;
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}
