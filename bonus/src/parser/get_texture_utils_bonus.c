/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:15:26 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 11:04:51 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	count_missing_identifier(t_data *data)
{
	int			cont;

	cont = 0;
	if (data->textures.no_flag != 1)
		cont++;
	if (data->textures.so_flag != 1)
		cont++;
	if (data->textures.we_flag != 1)
		cont++;
	if (data->textures.ea_flag != 1)
		cont++;
	if (data->textures.c_flag != 1)
		cont++;
	if (data->textures.f_flag != 1)
		cont++;
	return (cont);
}

void	set_new_fd(t_data *data, int cont, int *fd)
{
	int			missing;
	int			i;
	char		*line;

	i = 0;
	missing = count_missing_identifier(data);
	if (missing != 0)
	{
		close(*fd);
		*fd = open(data->file, O_RDONLY);
		if (*fd < 0)
		{
			print_error("Failed to open the map file. ");
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return ;
		}
		while (i <= cont - missing)
		{
			line = get_next_line(*fd);
			if (line && ft_strcmp(line, "\n"))
				i++;
			free(line);
		}
	}
}
