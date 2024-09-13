/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:03:54 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/13 11:31:45 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	find_player_position(t_data *data, char **map)
{
	int		i;
	int		j;
	char	c;

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
