/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:38:05 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 11:59:04 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	check_map_is_valid(t_data *data)
{
	int	flag;

	flag = 0;
	if (!data || !data->map.map)
		return (FAILURE);
	if (check_first_last_line(data, data->map.map))
		flag = 1;
	if (check_middle_lines(data->map.map))
		flag = 1;
	if (check_map_is_closed(data))
		flag = 1;
	if (check_players_in_map(data->map.map))
		flag = 1;
	if (check_if_valid_spaces(data->map.map))
		flag = 1;
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_map(char *file, t_data *data)
{
	int	fd;
	int	error_flag;

	error_flag = 0;
	if (check_map_extension(file, &error_flag))
		return (FAILURE);
	data->file = file;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error("Failed to open the map file. ");
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (FAILURE);
	}
	if (get_texture_data(data, &error_flag, &fd))
		error_flag = 1;
	if (get_map(data, fd))
		error_flag = 1;
	if (check_map_is_valid(data))
		error_flag = 1;
	close(fd);
	map_size(&data->map);
	return (error_flag);
}
