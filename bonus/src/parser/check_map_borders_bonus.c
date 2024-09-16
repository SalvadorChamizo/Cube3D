/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:46:02 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 11:04:15 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	check_side_walls(char **map)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		if (check_left_wall(map[i]))
		{
			print_border_error(i + 1, 1);
			flag = 1;
		}
		if (check_right_wall(map[i]))
		{
			print_border_error(i + 1, 2);
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}

int	check_left_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	check_right_wall(char *line)
{
	int	i;

	i = ft_strlen(line);
	i--;
	while (line[i] == ' ')
		i--;
	if (line[i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	check_first_line(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != ' ' && map[0][i] != '1')
		{
			print_error("Invalid character \"");
			ft_putchar_fd(map[0][i], 2);
			ft_putstr_fd("\" in map's first line.\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	check_last_line(char **map, int last_line)
{
	int	i;

	i = 0;
	while (map[last_line - 1][i])
	{
		if (map[last_line - 1][i] != ' ' && map[last_line - 1][i] != '1')
		{
			print_error("Invalid character \"");
			ft_putchar_fd(map[last_line - 1][i], 2);
			ft_putstr_fd("\" in map's last line.\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
