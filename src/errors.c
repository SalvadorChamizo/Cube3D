/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:17 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/30 17:48:55 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error(char *str)
{
	ft_putstr_fd(RED"Error: "RESET, 2);
	ft_putstr_fd(str, 2);
}

void	error_invalid_char(char **map, int line, int pos)
{
	print_error("Invalid character \"");
	ft_putchar_fd(map[line][pos], 2);
	ft_putstr_fd("\" in map at line ", 2);
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(pos + 1, 2);
	ft_putstr_fd(".\n", 2);
}

void	print_border_error(int line, int flag)
{
	if (flag == 1)
	{
		print_error("The left side of the map is not close at line ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
	if (flag == 2)
	{
		print_error("The right side of the map is not close at line ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
}