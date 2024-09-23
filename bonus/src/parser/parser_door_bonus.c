/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:46:19 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/17 12:11:48 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	manage_door_case(t_data *data)
{
	if (data->textures.do_flag != 1)
	{
		print_error("Detected door in map and ");
		ft_putstr_fd("\"DO\" identifier is missing\n", 2);
		data->textures.do_error = 1;
		return ;
	}
}
