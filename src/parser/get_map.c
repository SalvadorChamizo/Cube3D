/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:45:26 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/04 15:50:15 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_map(t_data *data, int fd)
{
	char	*line;
	char	*map;

	line = NULL;
	map = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		print_error("Failed reading map line.\n");
		return (FAILURE);
	}
	map = get_map_loop(line, fd);
	if (!map)
		return (FAILURE);
	map = ft_strtrim_safe(map, "\n");
	if (!map)
	{
		print_error("Failed in ft_strtrim_safe.\n");
		return (FAILURE);
	}
	if (get_map_error_and_split(data, map))
		return (FAILURE);
	return (SUCCESS);
}

char	*get_map_loop(char *line, int fd)
{
	char	*map;

	map = NULL;
	while (line)
	{
		if (!line)
		{
			print_error("Failed reading map line.\n");
			return (NULL);
		}
		map = ft_strjoin_safe(map, line);
		if (!map)
		{
			print_error("Failed in ft_strjoin_safe.\n");
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (map);
}

int	get_map_error_and_split(t_data *data, char *map)
{
	int	flag;

	flag = 0;
	if (check_extra_line(map))
		flag = 1;
	if (flag == 1)
	{
		free(map);
		return (FAILURE);
	}
	data->map.map = ft_split(map, '\n');
	free(map);
	if (!data->map.map)
	{
		print_error("Failed in ft_split at get_map().\n");
		return (FAILURE);
	}
	data->map.map_line = ft_split_size(data->map.map);
	return (SUCCESS);
}

int	check_extra_line(char *map)
{
	int	i;

	i = 0;
	if (!map || !map[i] || map[i] == '\n')
	{
		print_error("The map is missing.\n");
		return (FAILURE);
	}
	while (map[i])
	{
		if (map[i] == '\n')
		{
			i++;
			while (map[i] != '\0' && map[i] == ' ')
				i++;
			if (map[i] == '\n')
			{
				print_error("Extra line in map.\n");
				return (FAILURE);
			}
		}
		if (map[i] != '\0')
			i++;
	}
	return (SUCCESS);
}
