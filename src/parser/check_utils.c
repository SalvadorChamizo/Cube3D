/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:45:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/04 16:11:17 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_remove_nl(char *str)
{
	char	*new;

	new = ft_realloc(str, ft_strlen(str));
	if (!new)
		return (NULL);
	return (new);
}

int	ft_split_size(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	count_commas(char **color)
{
	int	i;
	int	j;
	int	cont;

	i = 0;
	cont = 0;
	while (color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (color[i][j] == ',')
				cont++;
			j++;
		}
		i++;
	}
	return (cont);
}

int	check_colors_format(char **path, int line)
{
	if (ft_strcmp(path[0], "C") && ft_strcmp(path[0], "F"))
		return (SUCCESS);
	if (ft_split_size(path) == 2 && count_commas(path) == 2)
		return (SUCCESS);
	else if (ft_split_size(path) == 4 && count_commas(path) == 2)
		return (SUCCESS);
	else
	{
		if (count_commas(path) != 2)
		{
			print_error("Invalid rgb format in line ");
			ft_putnbr_fd(line, 2);
			ft_putstr_fd(". ", 2);
			ft_putnbr_fd(count_commas(path) + 1, 2);
			ft_putstr_fd(" numbers detected.\n", 2);
		}
		if (ft_split_size(path) != 2 && ft_split_size(path) != 4)
		{
			print_error("Invalid rgb format in line ");
			ft_putnbr_fd(line, 2);
			ft_putstr_fd(". Too many arguments.\n", 2);
		}
		return (FAILURE);
	}
	return (SUCCESS);
}
