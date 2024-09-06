/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:21:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/06 14:53:59 by schamizo         ###   ########.fr       */
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
		ft_putstr_fd("\"\n", 2);
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

int	count_players_in_map(char **map)
{
	int	i;
	int	j;
	int	cont;

	i = 0;
	cont = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				cont++;
			j++;
		}
		i++;
	}
	return (cont);
}

int	check_players_in_map(char **map)
{
	int	player_num;

	player_num = count_players_in_map(map);
	if (player_num == 0)
	{
		print_error("Missing player in map.\n");
		return (FAILURE);
	}
	if (player_num > 1)
	{
		print_error("Too many players in map. Players detected: ");
		ft_putnbr_fd(player_num, 2);
		ft_putstr_fd("\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	angle_select(t_data *data, char c)
{
	if (c == 'N')
		data->player.angle = 270;
	if (c == 'S')
		data->player.angle = 90;
	if (c == 'W')
		data->player.angle = 180;
	if (c == 'E')
		data->player.angle = 0;
}

void	ray_init(t_data *data)
{
	double	fov_rad;
	double	angle_rad;
	int 	i;

	fov_rad = FOV * M_PI / 180;
	angle_rad = data->player.angle * M_PI / 180;
	i = 0;
	while (i < WIDTH)
	{
		data->player.ray[i].angle = angle_rad - (fov_rad / 2) + ((fov_rad / WIDTH) * i);
		if (data->player.ray[i].angle < 0)
			data->player.ray[i].angle += 2 * M_PI;
		i++;
	}
}

void	find_player_position(t_data *data, char **map)
{
	int	i;
	int	j;
	char c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				c = map[i][j];
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				data->player.map_x = j;
				data->player.map_y = i;
			}
			j++;
		}
		i++;
	}
	angle_select(data, c);
	ray_init(data);
}

int	check_map_is_valid(t_data *data)
{
	int	flag;

	flag = 0;
	if (check_first_last_line(data, data->map.map))
		flag = 1;
	if (check_middle_lines(data->map.map))
		flag = 1;
	if (check_map_is_closed(data))
		flag = 1;
	if (check_players_in_map(data->map.map))
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
	check_map_extension(file, &error_flag);
	fd = open(file, O_RDONLY);
	if (get_texture_data(data, &error_flag, fd))
		return (FAILURE);
	if (get_map(data, fd))
		return (FAILURE);
	if (check_map_is_valid(data))
		return (FAILURE);
	close(fd);
	return (error_flag);
}
